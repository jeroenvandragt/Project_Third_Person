#version 430

//uniform     vec3        cameraDirection;
uniform	    mat4        model;
uniform     sampler2D   colorMap;
uniform     vec3        light; // point light in world


in          vec2        fragTexCoord;   // uv
in          vec3        fragNormal;     // normal
in          vec3        fragVert;       // vertex

out         vec4        color;          // to screenbuffer

void main()
{
    vec3    lightPos                =   light ;
    vec3    ambientColor            =   vec3 ( 1.0f ,1.0f ,1.0f );  // this is the ambient color
    float   lightAttenuation        =   0.01f;                      // Loss of light intensity over distance.
    float   ambientCoefficient      =   0.1f;                       // ambient lighting
    vec3    materialSpecularColor   =   vec3 ( 1.0f ,1.0f ,1.0f );  // material color reflection
    float   materialShininess       =   80.0f;


    vec3    normal                  =   normalize( transpose ( inverse( mat3( model ) ) ) * fragNormal );
    vec3    surfacePos              =   vec3( model * vec4( fragVert , 1 ) );
    vec4    surfaceColor            =   texture( colorMap , fragTexCoord );
    vec3    surfaceToLight          =   normalize( lightPos - surfacePos );
    vec3    cameraDirection         =   vec3(0,5,0);
    vec3    surfaceToCamera         =   normalize( cameraDirection - surfacePos );

//-------------------------------------------------------------------------------------------------------------------------
//                  AMBIENT
//-------------------------------------------------------------------------------------------------------------------------

    vec3    ambient                 =   ambientCoefficient * surfaceColor.rgb * ambientColor;

//-------------------------------------------------------------------------------------------------------------------------
//                  DIFFUSE
//-------------------------------------------------------------------------------------------------------------------------

    float   diffuseCoefficient      =   max( 0.0 , dot( normal , surfaceToLight ) );
    vec3    diffuse                 =   diffuseCoefficient * surfaceColor.rgb * ambientColor;

//-------------------------------------------------------------------------------------------------------------------------
//                  SPECULAR
//-------------------------------------------------------------------------------------------------------------------------

    float   specularCoefficient     =   0.0;

    if( diffuseCoefficient > 0.0 )
        specularCoefficient = pow( max( 0.0 , dot( surfaceToCamera , reflect( -surfaceToLight , normal ) ) ) , materialShininess );

    vec3    specular                =   specularCoefficient * materialSpecularColor * ambientColor;


//-------------------------------------------------------------------------------------------------------------------------
//                  ATTENUATION (LIGHT INTENSITY OVER DISTANCE)
//-------------------------------------------------------------------------------------------------------------------------

    float   distanceToLight         =   length( lightPos - surfacePos );
    float   attenuation             =   1.0 / ( 1.0 + lightAttenuation * pow( distanceToLight, 2 ) );

//-------------------------------------------------------------------------------------------------------------------------
//                  LINEAR COLOR (BEFORE GAMMA)
//-------------------------------------------------------------------------------------------------------------------------

    vec3    linearColor             =   ambient + attenuation *( diffuse + specular );

//-------------------------------------------------------------------------------------------------------------------------
//                  FINAL COLOR (AFTER GAMMA)
//-------------------------------------------------------------------------------------------------------------------------
    vec3    gamma                   =   vec3( 1.0 / 2.2 );
    //color = vec4( pow( linearColor , gamma ) , surfaceColor.a );
    color = vec4( linearColor , surfaceColor.a );
}
