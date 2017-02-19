
#include "CTexture.h"


CTexture::CTexture(const char *filename)
{
	HMODULE hMod=GetModuleHandle(NULL);
    HRSRC hRes=FindResource(hMod,filename,"TGA");
    HGLOBAL hGlob=LoadResource(hMod,hRes);
    unsigned char *file_data=(unsigned char *)LockResource(hGlob);
	long file_size=SizeofResource(hMod,hRes);

	m_imageData=0;
	m_bpp=0;
	m_width=0;
	m_height=0;
	m_texID=0;

	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
	GLubyte		TGAcompare[12];
	GLubyte		header[6];
	GLuint		bytesPerPixel;
	GLuint		imageSize;
	GLuint		temp;
	GLuint		type=GL_RGBA;

	memcpy(header,file_data+sizeof(TGAcompare),sizeof(header));

	m_width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	m_height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	m_bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= m_bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= m_width*m_height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	m_imageData=new GLubyte[imageSize];

	memcpy(m_imageData, file_data+sizeof(TGAcompare)+sizeof(header), imageSize);

	for(GLint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=m_imageData[i];							// Temporarily Store The Value At Image Data 'i'
		m_imageData[i] = m_imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		m_imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	// Build A Texture From The Data
	glGenTextures(1, &m_texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, m_texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (m_bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, m_width, m_height, 0, type, GL_UNSIGNED_BYTE, m_imageData);

}


CTexture::~CTexture()
{
    delete [] m_imageData;
}


GLuint CTexture::GetTexID()
{
    return m_texID;
}
