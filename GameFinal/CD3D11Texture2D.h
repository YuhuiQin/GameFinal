#ifndef __CD3D11TEXTURE2D_H_INCLUDE__
#define __CD3D11TEXTURE2D_H_INCLUDE__

#include "ITexture.h"
#include "CD3D11Driver.h"
#include "CD3D11RenderTarget.h"
#include "CD3D11DepthStencilSurface.h"

namespace gf
{
	class CD3D11Texture2D : public ITexture
	{
	public:
		CD3D11Texture2D(ID3D11Device* pd3dDevice, 
			ID3D11DeviceContext* pd3dDeviceContext, 
			const std::string& name, u32 sortCode,
			CD3D11Driver* d3d11Driver);

		bool loadFromFile(const std::string& filename);

		bool create(u32 width, u32 height, u32 bindFlags, 
			void* rawData, u32 miplevel, 
			E_GI_FORMAT format, u32 pitch = 0, 
			E_MEMORY_USAGE memoryUsage = EMU_UNKNOWN);

		bool createDepthStencilTexture(u32 width, u32 height,
			u32 depthBitNum, u32 stencilBitNum,
			bool multiSampling, u32 multiSamplingCount, u32 multiSamplingQuality,
			bool bShaderBound = true, bool bindDepthToShader = true);

		ID3D11ShaderResourceView* getShaderResourceView()
		{
			return md3dSRV;
		}

		virtual E_TEXTURE_TYPE getType() const
		{
			return ETT_TEXTURE_2D;
		}

		virtual u32 getWidth() const
		{
			return mTextureWidth;
		}

		virtual u32 getHeight() const
		{
			return mTextureHeight;
		}

		virtual IRenderTarget* getRenderTarget(u32 index = 0)
		{
			return mRenderTarget;
		}

		virtual IDepthStencilSurface* getDepthStencilSurface(u32 index = 0)
		{
			return mDepthStencilSurface;
		}

		virtual void apply(E_SHADER_TYPE shaderType, u32 slot, 
			E_TEXTURE_BIND_TYPE bindType = ETBT_SHADER_RESOURCE);

		virtual u32 getElementSize() const;

		virtual bool copyDataToAnotherTexture(ITexture* dest);

		virtual bool lock(E_TEXTURE_LOCK_TYPE lockType, STextureData* texData, u32 index = 0);

		virtual void unlock();

		virtual ~CD3D11Texture2D();

	private:
		ID3D11Device*					md3dDevice;
		ID3D11DeviceContext*			md3dDeviceContext;
		CD3D11Driver*					md3d11Driver;
		ID3D11Texture2D*				md3dTexture;
		ID3D11ShaderResourceView*		md3dSRV;
		ID3D11UnorderedAccessView*		md3dUAV;
		
		u32								mTextureWidth;
		u32								mTextureHeight;
		u32								mBindFlags;

		CD3D11RenderTarget*				mRenderTarget;
		CD3D11DepthStencilSurface*		mDepthStencilSurface;
	};
}
#endif
