// Text Header
#ifndef _H_TEXT_
#define _H_TEXT_

// Common includes
#include "Common.h"
#include "uString.h"

#define MAX_TEXTS 0x7fffffff

#define AGK_TEXT_REFRESHING			0x01
#define AGK_TEXT_BOLD				0x02
#define AGK_TEXT_OVERRIDE_SCISSOR	0x04
#define AGK_TEXT_SNAP_TO_PIXELS		0x08

// Namespace
namespace AGK
{
	class cSprite;
	class cSpriteMgrEx;
	class AGKFont;
	class AGKSizedFont;

	class cText
	{
		protected:
			
			friend class agk;

			struct sTextUniform
			{
				uString m_sName;
				int index;
				float v1;
				float v2;
				float v3;
				float v4;

				sTextUniform() { index = -1; v1 = 0; v2 = 0; v3 = 0; v4 = 0; };
				sTextUniform(const sTextUniform* pOther) { m_sName.SetStr(pOther->m_sName); index = pOther->index; v1 = pOther->v1; v2 = pOther->v2; v3 = pOther->v3; v4 = pOther->v4; };
				~sTextUniform() {}
			};

			static UINT g_iCreated;

			UINT m_iCreated;
			UINT m_iID;
			uString m_sText;
			UINT m_iNumSprites;
			cSprite **m_pSprites;
			unsigned char *m_pCharStyles;
			float m_fX;
			float m_fY;
			float m_fSpriteX;
			float m_fSpriteY;
			float m_fAngle;
			int m_iDepth;
			float m_fOrigSize;
			float m_fSize;
			//float m_fHeight;
			float m_fTotalWidth;
			float m_fTotalHeight;
			float m_fSpacing;
			float m_fVSpacing;
			bool m_bVisible;
			int m_iRed;
			int m_iGreen;
			int m_iBlue;
			int m_iAlpha;
			int m_iAlign;
			int m_iVAlign;
			int m_iTransparency;
			bool m_bManagedDrawing; // true if the drawing is handled by a sprite manager
			cSpriteMgrEx* m_pSpriteManager;
			int m_iFixed;
			float m_fMaxWidth;
			UINT m_iLines;
			UINT m_bFlags;

			// shader variables
			AGKShader* m_pShader;
			cHashedList<sTextUniform> m_cShaderVariables;

			float		m_fClipX;
			float		m_fClipY;
			float		m_fClipX2;
			float		m_fClipY2;

			float *pVertices;
			float *pUV;
			unsigned char *pColor;
			unsigned short *pIndices;

			bool m_bDepthChanged;
			bool m_bTextureChanged;
			bool m_bTransparencyChanged;

			UINT m_iImageID;
			cImage *m_pFontImage;
			cImage **m_pLetterImages;

			cImage *m_pFontImageExt;
			cImage **m_pLetterImagesExt;

			static cImage *m_pDefaultFontOrig;
			static cImage *m_pDefaultFontExtOrig;

			static cImage *m_pDefaultFont;
			static cImage **m_pDefaultLetters;

			static cImage *m_pDefaultFontExt;
			static cImage **m_pDefaultLettersExt;

			cImage *m_pUsingDefaultFont;
			cImage *m_pUsingDefaultFontExt;

			// new fonts
			AGKFont *m_pFTFont;
			AGKSizedFont *m_pFTSizedFont;
			float m_fHorizontalRatio;
			float m_fVerticalRatio;
			float m_fFontScale;
			
			void PlatformDraw();
			void PlatformDrawFT(); // FreeType
			void UpdateManager();
			void InternalRefresh();
			void InternalSetShader(AGKShader* shader);

		public:

			static void SetDefaultMinFilter( UINT mode );
			static void SetDefaultMagFilter( UINT mode );
			static void SetDefaultFontImage( cImage *pImage ); 
			static void SetDefaultExtendedFontImage( cImage *pImage ); 

			static const cImage* GetDefaultFontImage() { return m_pDefaultFont; }
			static const cImage* GetDefaultFontExtImage() { return m_pDefaultFontExt; }

			cText( int iLength=0 );
			~cText();
			UINT GetCreated() const { return m_iCreated; }
			void SetSpriteManager( cSpriteMgrEx *pMgr );

			static void GlobalImageDeleting( cImage *pImage );
			void ImageDeleting( cImage *pImage );
			
			void ChangedAspect();
			void SetString( const uString &sString ) { SetString( sString.GetStr() ); }
			void SetString( const char* szString );
			void SetPosition( float fX, float fY );
			void ReAlignSprites();
			void ShiftPosition( float fDiffX, float fDiffY );
			void SetX( float fX );
			void SetY( float fY );
			void SetAngle( float fA );
			void SetAngleRad( float fA );
			void SetSize( float fSize );
			void SetSpacing( float fSpacing );
			void SetLineSpacing( float fSpacing );
			void SetAlignment( int iMode );
			void SetDepth( int iDepth );
			void SetVisible( bool bVisible );
			void SetColor( UINT iRed, UINT iGreen, UINT iBlue, UINT iAlpha=255 );
			void SetRed( UINT iRed );
			void SetGreen( UINT iGreen );
			void SetBlue( UINT iBlue );
			void SetAlpha( UINT iAlpha );
			void SetTransparency( int iMode );
			void SetMaxWidth( float width );
			void SetBold( UINT bold );
			void SetOverrideScissor( int mode );
			void SetSnap( int mode );

			void SetCharPosition( UINT iIndex, float x, float y );
			void SetCharX( UINT iIndex, float x );
			void SetCharY( UINT iIndex, float y );
			void SetCharAngle( UINT iIndex, float angle );
			void SetCharAngleRad( UINT iIndex, float angle );
			void SetCharColor( UINT iIndex, UINT red, UINT green, UINT blue, UINT alpha );
			void SetCharRed( UINT iIndex, UINT iRed );
			void SetCharGreen( UINT iIndex, UINT iGreen );
			void SetCharBlue( UINT iIndex, UINT iBlue );
			void SetCharAlpha( UINT iIndex, UINT iAlpha );
			void SetCharBold( UINT index, UINT bold );
			float GetCharX( UINT iIndex );
			float GetCharY( UINT iIndex );
			float GetCharWidth( UINT iIndex );
			float GetCharAngle( UINT iIndex );
			float GetCharAngleRad( UINT iIndex );
			UINT GetCharRed( UINT iIndex );
			UINT GetCharGreen( UINT iIndex );
			UINT GetCharBlue( UINT iIndex );
			UINT GetCharAlpha( UINT iIndex );
			unsigned char GetChar( UINT iIndex );

			bool GetHitTest( float x, float y );
			void FixToScreen( int mode );
			void SetFontImage( cImage *pImage ); // use either SetFontImage or SetFont, not both
			void SetExtendedFontImage( cImage *pImage ); 
			void SetFont( AGKFont *pFont ); // use either SetFontImage or SetFont, not both
			void Refresh();
			
			float GetX( );
			float GetY( );
			float GetZ( ) { return m_iDepth / 10000.0f; }
			float GetAngle( );
			float GetAngleRad( );
			UINT GetLength( );
			UINT GetRed() { return m_iRed; }
			UINT GetGreen() { return m_iGreen; }
			UINT GetBlue() { return m_iBlue; }
			UINT GetAlpha() { return m_iAlpha; }
			int GetTransparency() { return m_iTransparency; }
			float GetTotalWidth() { return m_fTotalWidth; }
			float GetTotalHeight() { return m_fTotalHeight; }
			bool GetVisible() { return m_bVisible; }
			int GetDepth() { return m_iDepth; }
			float GetSize() { return m_fSize; }
			void GetText( uString &out ) { out.SetStr( m_sText ); }
			UINT GetLines() { return m_iLines; }
			float GetSpacing() { return m_fSpacing; }
			float GetLineSpacing() { return m_fVSpacing; }
			int GetAlignment() { return m_iAlign; }

			AGKShader* GetShader() { return m_pShader; }
			void SetShader(AGKShader* shader);
			void SetShaderConstantByName(const char* name, float v1, float v2, float v3, float v4);
			void SetShaderConstantArrayByName(const char* name, UINT index, float v1, float v2, float v3, float v4);
			void SetShaderConstantDefault(const char* name);

			bool CheckDepthChanged() 
			{
				bool bChanged = m_bDepthChanged;
				return bChanged; 
			}
			bool GetDepthChanged() 
			{
				bool bChanged = m_bDepthChanged;
				m_bDepthChanged = false;
				return bChanged; 
			}
			bool GetTextureChanged() 
			{ 
				bool bChanged = m_bTextureChanged;
				m_bTextureChanged = false;
				return bChanged; 
			}
			bool GetTransparencyChanged() 
			{ 
				bool bChanged = m_bTransparencyChanged;
				m_bTransparencyChanged = false;
				return bChanged; 
			}
			
			bool IsManaged() { return m_bManagedDrawing; }

			void SetScissor( float x, float y, float x2, float y2 );
			void GetClipValues( int &x, int &y, int &width, int &height );

			void Draw();
			void Update( float time );
	};
}

#endif
