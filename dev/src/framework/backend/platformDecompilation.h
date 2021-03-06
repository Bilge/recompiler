#pragma once

namespace code
{
	class Generator;
}

namespace decoding
{
	class Context;
}

namespace platform
{

	//---------------------------------------------------------------------------

	/// Platform decompilation interface (loaded from DLL)
	class RECOMPILER_API DecompilationInterface
	{
	public:
		//! Release the interface
		virtual void Release() = 0;

		//! Get internal platform name
		virtual const char* GetName() const = 0;

		//! Get name of the export library 
		virtual const char* GetExportLibrary() const = 0;

		//! Get path to platform includes (for compilation)
		virtual const wchar_t* GetIncludeDirectory() const = 0;

		//----

		//! Get number of supported extensions
		virtual const uint32 GetNumExtensions() const = 0;

		//! Get supported file extension
		virtual const char* GetExtension( const uint32 index ) const = 0;

		//! Get supported file extension name
		virtual const char* GetExtensionName( const uint32 index ) const = 0;

		//----

		//! Get number of CPUs supported by this platform
		virtual const uint32 GetNumCPU() const = 0;

		//! Get cpu definition
		virtual const CPU* GetCPU( const uint32 index ) const = 0;

		//----

		//! Load given image (absolute path given), returns loader with all modules
		virtual image::Binary* LoadImageFromFile( class ILogOutput& log, const platform::Definition* platform, const wchar_t* absolutePath ) const = 0;

		//! Decode image instructions, resolve jumps and initial block locations, usually done only once, returns false on critical errors
		virtual bool DecodeImage( ILogOutput& log, decoding::Context& decodingContext ) const = 0;

		//! Export code from image
		virtual bool ExportCode( ILogOutput& log, decoding::Context& decodingContext, code::Generator& generator ) const = 0;

	protected:
		virtual ~DecompilationInterface() {};
	};

	//---------------------------------------------------------------------------

	typedef DecompilationInterface* (__stdcall *TCreatePlatformInterface)(const int callerInterfaceVersion);

	//---------------------------------------------------------------------------

} // platform