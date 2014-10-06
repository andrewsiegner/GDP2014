#ifndef _CPlyFile5nt_DX11_HG_
#define _CPlyFile5nt_DX11_HG_

// Written by Michael Feeney, Fanshawe College, 2009-2010
// mfeeney@fanshawec.ca
// It may be distributed under the terms of the General Public License:
// http://www.fsf.org/licenses/gpl.html
// Use this code at your own risk. It is indented only as a learning aid.

// Fairly simple PLY file loader that also calculates the normal for the model.
//  Note that it assumes a certain winding order...
//	Can load the Stanford Bunny and most (?) other files from the 
//	The Stanford 3D Scanning Repository
//	http://graphics.stanford.edu/data/3Dscanrep/
// (Well, I haven't tested them all, but it loads the bunny, dragon, and armadillo...)
//
// Very simply ply reader that also calculates the normal for the model.
//
// See Greg Turk's paper and details of the bunny here:
// http://www.cc.gatech.edu/~turk/bunny/bunny.html

// Written by Michael Feeney, Fanshawe College, 2010
// mfeeney@fanshawec.on.ca
// It may be distributed under the terms of the General Public License:
// http://www.fsf.org/licenses/gpl.html
// Use this code at your own risk. It is indented only as a learning aid.
//
#include <string>
#include <vector>
#include "CVector3f.h"


// This structure holds the vertex information 
// as listed in the bunny file
struct PLYVERTEX
{
	// **** ADDED THIS ****
	PLYVERTEX(): nx(0.0f), ny(0.0f), nz(0.0f), 
				 tex0u(0.0f), tex0v(0.0f), tex1u(0.0f), tex1v(0.0f),
				 red(0), green(0), blue(0) {}
	CVector3f xyz; 
	//float x, y, z;
	float nx, ny, nz;
	float tex0u, tex0v;
	float tex1u, tex1v;
	// *********************
	float red, green, blue;
};

// This structure holds the elements, which 
// refer to the vertex indicies
struct PLYELEMENT
{
	// **** ADDED THIS ****
	PLYELEMENT(): vertex_index_1(0), vertex_index_2(0), vertex_index_3(0) {}
	int vertex_index_1;
	int vertex_index_2;
	int vertex_index_3;
};

struct CFileInfo
{
public:
	std::wstring fileName;
	enum enumFileType
	{
		MODEL_FILE_TYPE_PLY,
		MODEL_FILE_TYPE_GDP,
		MODEL_FILE_TYPE_UNKNOWN
	};	
	enumFileType fileType;
	CFileInfo() : fileType(MODEL_FILE_TYPE_UNKNOWN){};
	CFileInfo( std::wstring fileName, enumFileType fileType ) : fileName(fileName), fileType(fileType) {};
};

class CPlyFile5nt
{
public:
	CPlyFile5nt();
	~CPlyFile5nt();
	CPlyFile5nt( const CPlyFile5nt &rhs );	// Copy constructor
	CPlyFile5nt& operator=( const CPlyFile5nt &rhs );

	CFileInfo m_fileInformation;

	// error returns the reason for failure
	bool OpenPLYFile(std::wstring fileName, std::wstring &error);
	bool SaveGDPFile(std::wstring fileName, bool bOverwrite, std::wstring &error);
	bool OpenGDPFile(std::wstring fileName, std::wstring &error);	// GDP model format (basically a binary PLY version)
	// reads only the header information (number of vertices, etc.)
	bool ReadPLYFileHeader(std::wstring fileName, std::wstring &error);
	bool ReadGDPFileHeader(std::wstring fileName, std::wstring &error);
	
	int GetNumberOfVerticies(void);
	int GetNumberOfElements(void);
	PLYVERTEX getVertex_at(std::vector<PLYVERTEX>::size_type index);
	PLYELEMENT getElement_at(std::vector<PLYELEMENT>::size_type index);
	float getMaxX(void); float getMinX(void); float getDeltaX(void);
	float getMaxY(void); float getMinY(void); float getDeltaY(void);
	float getMaxZ(void); float getMinZ(void); float getDeltaZ(void);
	float getMaxExtent(void);
	// *********************
	void normalizeTheModelBaby_Rock_n_Roll(void);
	//void normalizeTheModelBabyDirectXVersion_Rock_n_Roll(void);
	void normalizeTheModelBaby(void);
	void normalizeTheModelBabyDirectXVersion(void);

	enum enumTEXCOORDBIAS
	{
		POSITIVE_X, POSITIVE_Y, POSITIVE_Z
	};

	void GenTextureCoordsSpherical( enumTEXCOORDBIAS uBias, enumTEXCOORDBIAS vBias, bool basedOnNormals, float scale, bool fast );
	
	unsigned int GetID(void);
	// Added: March 14, 2012
	bool bHadTextureCoordinatesInFile(void);
	bool bHadNormalsInFile(void);
	// Added: June 8, 2013
	void normlizeExistingNomrals(void);	
	// End of Added

	void scaleVertices( float scaleFactor );
	void calcualteExtents(void);

private:
	std::vector<PLYVERTEX> m_verticies;
	std::vector<PLYELEMENT> m_elements;
	float m_minX, m_maxX, m_deltaX;
	float m_minY, m_maxY, m_deltaY;
	float m_minZ, m_maxZ, m_deltaZ;
	// *********************
	float m_centreX, m_centreY, m_centreZ;
	float m_maxExtent;

	int m_numberOfVertices;
	int m_numberOfElements;

	// **********************************************************
	// **** Because the ply files can be of various formats, ****
	// ****	 this code is to allow loading 'most' ply files  ****
	// ****  not just the ones that are the 'Stanford bunny' ****
	// ****  format.                                         ****
	// **********************************************************
	int m_totalProperties;
	int m_x_propertyIndex;
	int m_y_propertyIndex;
	int m_z_propertyIndex;
	int m_normx_propertyIndex;
	int m_normy_propertyIndex;
	int m_normz_propertyIndex;
	int m_red_propertyIndex;
	int m_green_propertyIndex;
	int m_blue_propertyIndex;

	// Added: March 14, 2012
	bool m_bHadTextureCoordinatesInFile;
	bool m_bHadNormalsInFile;
	int m_tex0u_propertyIndex;		// "u"
	int m_tex0v_propertyIndex;		// "v"
	int m_tex1u_propertyIndex;		// "tex1u"
	int m_tex1v_propertyIndex;		// "tex1v"
	int m_UNKNOWN_IGNORE_propertyIndex;		// This is used when we don't know what they heck this index is.
	// End of Added

	// 
	void m_setIndexBasedOnPropertyName(int curIndex, std::wstring propName);
	bool m_placeItemInAppropriateVertexLocation( std::wstring tempString, int propertyIndex, PLYVERTEX &tempVertex );

	unsigned int m_ID;
	static unsigned int statNextID;

};



#endif