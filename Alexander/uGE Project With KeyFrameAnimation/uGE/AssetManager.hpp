#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>

namespace uGE {

	class Mesh;
	class Texture;
	class AssetManager
	{
		private:
			static std::map< std::string, Mesh * > meshes;
			static std::map< std::string, Texture * > textures;
		public:
			AssetManager();
			virtual ~AssetManager();

			static Mesh * loadMesh( std::string file );
			//Sound * loadSound( std::string file );
			static Texture * loadTexture( std::string file );

	};
}
#endif // ASSETMANAGER_H
