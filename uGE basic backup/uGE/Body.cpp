#include "Body.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"


namespace uGE {

	Body::Body( GameObject * parent )
	:	_parent( parent ), _mesh( 0 ), _colorMap1( 0 ), _colorMap2( 0 ), _colorMap3( 0 ), _colorMap4( 0 ), _heightMap( 0 ), _splatMap( 0 ), _shader( 0 )
	{
//		parent->set( this );
	}

	Body::~Body()
	{
		//dtor
	}

	void Body::render( Shader * shader, glm::mat4 & transform )
	{
		if ( shader && _mesh ) {
			shader->setUniform( shader->model, transform );
			if ( _colorMap1 ) shader->setTexture( shader->colorMap1, 0, _colorMap1 );
			if ( _colorMap2 ) shader->setTexture( shader->colorMap2, 1, _colorMap2 );
			if ( _colorMap3 ) shader->setTexture( shader->colorMap3, 2, _colorMap3 );
			if ( _colorMap4 ) shader->setTexture( shader->colorMap4, 3, _colorMap4 );
            if ( _heightMap ) shader->setTexture( shader->heightMap, 4, _heightMap );
            if ( _splatMap ) shader->setTexture( shader->splatMap, 5, _splatMap );

			shader->setAttrib( _mesh->getIndexBuffer() );
			shader->setAttrib( shader->vertex, 3, _mesh->getVertexBuffer() );
			shader->setAttrib( shader->normal, 3, _mesh->getNormalBuffer() );
			shader->setAttrib( shader->uv, 		 2, _mesh->getUvBuffer() );
			shader->render( _mesh->size() );
		}
	}
	void Body::setShader( Shader * shader)
	{
	    _shader = shader;
	}

	Shader * Body::getShader()
	{
	    return _shader;
	}

	void Body::setMesh( Mesh * mesh )
	{
		_mesh = mesh;
	}

	void Body::setTexture1( Texture * texture )
	{
		_colorMap1 = texture;
	}

	void Body::setTexture2( Texture * texture )
	{
		_colorMap2 = texture;
	}

	void Body::setTexture3( Texture * texture )
	{
		_colorMap3 = texture;
	}
	void Body::setTexture4( Texture * texture )
	{
		_colorMap4 = texture;
	}

	void Body::setHeightMap( Texture * texture )
	{
		_heightMap = texture;
	}

	void Body::setSplatMap( Texture * texture )
	{
		_splatMap = texture;
	}
}
