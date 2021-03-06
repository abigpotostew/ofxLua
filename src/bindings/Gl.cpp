/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "ofFbo.h"
#include "ofGLUtils.h"
#include "ofLight.h"
#include "ofMaterial.h"
#include "ofShader.h"
#include "ofTexture.h"
#include "ofVbo.h"
#include "ofVboMesh.h"
#include "ofAppRunner.h"
#include "ofxLua.h"
#include <luabind/operator.hpp>

namespace bindings {

// dummy classes for empty class enums

struct PrimitiveMode {};
struct PolyRenderMode {};
struct LightType {};
struct TexCompression {};
struct TexWrapDummy{};

// wrapper functions needed for overloading

void fboAllocate3(ofFbo *fbo, int width, int height, int internalformat)
	{fbo->allocate(width, height, internalformat);}
void fboAllocate2(ofFbo *fbo, int width, int height)
	{fbo->allocate(width, height);}
void fboAllocate0(ofFbo *fbo) {fbo->allocate();}
void fboBegin0(ofFbo *fbo) {fbo->begin();}
void fboReadToPixels1(ofFbo *fbo, ofPixels &pixels) {fbo->readToPixels(pixels);}

void setGlobalAmbientColor3(int r, int g, int b)
	{ofSetGlobalAmbientColor(ofColor(r, g, b));}
void setGlobalAmbientColor4(int r, int g, int b, int a)
	{ofSetGlobalAmbientColor(ofColor(r, g, b, a));}
void setGlobalAmbientHexColor(int color)
	{ofSetGlobalAmbientColor(ofColor(color));}

void lightSetSpotlight0(ofLight* light) {light->setSpotlight();}
void lightSetSpotlight1(ofLight* light, float spotCutoff)
	{light->setSpotlight(spotCutoff);}
void lightSetAttenuation0(ofLight* light)
	{light->setAttenuation();}
void lightSetAttenuation1(ofLight* light, float constant)
	{light->setAttenuation(constant);}
void lightSetAmbientColor3(ofLight* light, int r, int g, int b)
	{light->setAmbientColor(ofColor(r, g, b));}
void lightSetAmbientColor4(ofLight* light, int r, int g, int b, int a)
	{light->setAmbientColor(ofColor(r, g, b, a));}
void lightSetAmbientHexColor(ofLight* light, int color)
	{light->setAmbientColor(ofColor(color));}
void lightSetDiffuseColor3(ofLight* light, int r, int g, int b)
	{light->setDiffuseColor(ofColor(r, g, b));}
void lightSetDiffuseColor4(ofLight* light, int r, int g, int b, int a)
	{light->setDiffuseColor(ofColor(r, g, b, a));}
void lightSetDiffuseHexColor(ofLight* light, int color)
	{light->setDiffuseColor(ofColor(color));}
void lightSetSpecularColor3(ofLight* light, int r, int g, int b)
	{light->setSpecularColor(ofColor(r, g, b));}
void lightSetSpecularColor4(ofLight* light, int r, int g, int b, int a)
	{light->setSpecularColor(ofColor(r, g, b, a));}
void lightSetSpecularHexColor(ofLight* light, int color)
	{light->setSpecularColor(ofColor(color));}

bool shaderLoad2(ofShader *shader, string vertName, string fragName)
	{return shader->load(vertName, fragName);}

void setMinMagFilters0() {ofSetMinMagFilters();}
void setMinMagFilters1(GLfloat minFilter) {ofSetMinMagFilters(minFilter);}
    
void setTextureWrapRepeat0(){
    ofSetTextureWrap(GL_REPEAT, GL_REPEAT);
}
void setTextureWrapRepeat1(ofTexture* t){
    t->setTextureWrap(GL_REPEAT, GL_REPEAT);
}

void textureLoadScreenData0(ofTexture* texture)
	{texture->loadScreenData(0, 0, ofGetWidth(), ofGetHeight());}
int textureGetType(ofTexture* texture)
	{return texture->getTextureData().glTypeInternal;}
void textureSetFlip(ofTexture* texture, bool flip)
	{texture->getTextureData().bFlipTexture = flip;}
bool textureGetFlip(ofTexture* texture)
	{return texture->getTextureData().bFlipTexture;}
float textureGetTexT(ofTexture* texture)
	{return texture->getTextureData().tex_t;}
void textureSetTexT(ofTexture* texture, float tex_t)
	{texture->getTextureData().tex_t = tex_t;}
float textureGetTexU(ofTexture* texture)
	{return texture->getTextureData().tex_u;}
void textureSetTexU(ofTexture* texture, float tex_u)
	{texture->getTextureData().tex_u = tex_u;}
float textureGetTexW(ofTexture* texture)
	{return texture->getTextureData().tex_w;}
void textureSetTexW(ofTexture* texture, float tex_w)
	{texture->getTextureData().tex_t = tex_w;}
float textureGetTexH(ofTexture* texture)
	{return texture->getTextureData().tex_h;}
void textureSetTexH(ofTexture* texture, float tex_h)
	{texture->getTextureData().tex_t = tex_h;}
void bindTexture(ofTexture* texture)
	{texture->bind();}
void unbindTexture(ofTexture* texture)
	{texture->unbind();}
  
// for adding to a vbo mesh
void addVertexVboMesh(ofVboMesh* vbo_mesh, float x, float y, float z){
    vbo_mesh->addVertex(ofVec3f(x,y,z));
}
void addTexCoordVboMesh(ofVboMesh* vbo_mesh, float u, float v){
    vbo_mesh->addTexCoord(ofVec2f(u,v));
}
void addNormalVboMesh(ofVboMesh* vbo_mesh, float x, float y, float z){
    vbo_mesh->addNormal(ofVec3f(x,y,z));
}
void addColorAVboMesh(ofVboMesh* vbo_mesh, float r, float g, float b, float a){
    vbo_mesh->addColor(ofFloatColor(r,g,b,a));
}
void addColorVboMesh(ofVboMesh* vbo_mesh, float r, float g, float b){
    addColorAVboMesh(vbo_mesh,r,g,b,255.0f);
}
void addIndexVboMesh(ofVboMesh* vbo_mesh, ofIndexType i){
    vbo_mesh->addIndex(i);
}

// luabind registration
luabind::scope registerGl() {
		
	using namespace luabind;
	
	return
		
    
    
		///////////////////////////////
		/// \section ofFbo.h
		
		class_<ofFbo>("Fbo")
			.def(constructor<>())
			.def(constructor<const ofFbo&>())
			
			.def("allocate", (void(ofFbo::*)(int,int,int,int)) &ofFbo::allocate)
			.def("allocate", (void(ofFbo::*)(ofFbo::Settings)) &ofFbo::allocate)
			.def("isAllocated", &ofFbo::isAllocated)
			
			.def("draw", (void(ofFbo::*)(float,float)) &ofFbo::draw)
			.def("draw", (void(ofFbo::*)(float,float,float,float)) &ofFbo::draw)
			
			.def("setAnchorPercent", &ofFbo::setAnchorPercent)
			.def("setAnchorPoint", &ofFbo::setAnchorPoint)
			.def("resetAnchor", &ofFbo::resetAnchor)
			
			.def("setDefaultTextureIndex", &ofFbo::setDefaultTextureIndex)
			.def("getDefaultTextureIndex", &ofFbo::getDefaultTextureIndex)
			
			.def("getTextureReference", (ofTexture&(ofFbo::*)(void)) &ofFbo::getTextureReference)
			.def("getTextureReference", (ofTexture&(ofFbo::*)(int)) &ofFbo::getTextureReference)
			.def("getDepthTexture", &ofFbo::getDepthTexture)
			.def("setUseTexture", &ofFbo::setUseTexture)
			
			.def("beginFbo", &fboBegin0)
			.def("beginFbo", &ofFbo::begin)
			.def("endFbo", &ofFbo::end)
			
			.def("readToPixels", &fboReadToPixels1)
			.def("readToPixels", (void(ofFbo::*)(ofPixels&,int)) &ofFbo::readToPixels)
			// ignore shortPixels & floatPixels functions for now
			
			.def("getWidth", &ofFbo::getWidth)
			.def("getHeight", &ofFbo::getWidth)
			.property("width", &ofFbo::getWidth)
			.property("height", &ofFbo::getHeight)
			
			// ignoring "advanced functions" for now ...
			
			.scope [ // settings struct
				class_<ofFbo::Settings>("Settings")
					.def(constructor<>())
					.def_readwrite("width", &ofFbo::Settings::width)
					.def_readwrite("height", &ofFbo::Settings::height)
					.def_readwrite("numColorBuffers", &ofFbo::Settings::numColorbuffers)
					.def_readwrite("colorFormats", &ofFbo::Settings::colorFormats)
					.def_readwrite("useDepth", &ofFbo::Settings::useDepth)
					.def_readwrite("useStencil", &ofFbo::Settings::useStencil)
					.def_readwrite("depthStencilAsTexture", &ofFbo::Settings::depthStencilAsTexture)
					.def_readwrite("textureTarget", &ofFbo::Settings::textureTarget)
					.def_readwrite("internalFormat", &ofFbo::Settings::internalformat)
					.def_readwrite("depthStencilInternalFormat", &ofFbo::Settings::depthStencilInternalFormat)
					.def_readwrite("wrapModeHorizontal", &ofFbo::Settings::wrapModeHorizontal)
					.def_readwrite("minFilter", &ofFbo::Settings::minFilter)
					.def_readwrite("maxFilter", &ofFbo::Settings::maxFilter)
					.def_readwrite("numSamples", &ofFbo::Settings::numSamples)
			],
    
    
			
		///////////////////////////////
		/// \section of3dUtils.h
		//Use with of.PRIMITIVE.x
		class_<PrimitiveMode>("PRIMITIVE")
			.enum_("mode") [
				value("TRIANGLES", OF_PRIMITIVE_TRIANGLES),
				value("TRIANGLE_STRIP", OF_PRIMITIVE_TRIANGLE_STRIP),
				value("TRIANGLE_FAN", OF_PRIMITIVE_TRIANGLE_FAN),
				value("LINES", OF_PRIMITIVE_LINES),
				value("LINE_STRIP", OF_PRIMITIVE_LINE_LOOP),
				value("LINE_LOOP", OF_PRIMITIVE_LINE_LOOP),
				value("POINTS", OF_PRIMITIVE_POINTS)
			],
			
		class_<PolyRenderMode>("MESH")
			.enum_("mode") [
				value("POINTS", OF_MESH_POINTS),
				value("WIREFRAME", OF_MESH_WIREFRAME),
				value("FILL", OF_MESH_FILL)
			],
			
		// leaving out OF <-> GL conversion functions
		
		///////////////////////////////
		/// \section ofLight.h
		
		class_<LightType>("LIGHT")
			.enum_("type") [
				value("POINT", OF_LIGHT_POINT),
				value("SPOT", OF_LIGHT_SPOT),
				value("DIRECTIONAL", OF_LIGHT_DIRECTIONAL)
			],
		
		def("enableLighting", &ofEnableLighting),
		def("disableLighting", &ofDisableLighting),
		def("enableSeparateSpecularLight", &ofEnableSeparateSpecularLight),
		def("disableSeparateSpecularLight", &ofDisableSeparateSpecularLight),
		def("getLightingEnabled", &ofGetLightingEnabled),
		def("setSmoothLighting", &ofSetSmoothLighting),
		def("setGlobalAmbientColor", &ofSetGlobalAmbientColor),
		def("setGlobalAmbientColor", &setGlobalAmbientColor3),
		def("setGlobalAmbientColor", &setGlobalAmbientColor4),
		def("setGlobalAmbientHexColor", &setGlobalAmbientHexColor),
		
		class_<ofLight>("Light")
			.def(constructor<>())
			.def(constructor<const ofLight&>())
			.def("destroy", &ofLight::destroy)
			
			.def("setup", &ofLight::setup)
			.def("enable", &ofLight::enable)
			.def("disable", &ofLight::disable)
			.def("getIsEnabled", &ofLight::getIsEnabled)
			.property("enabled", &ofLight::getIsEnabled)
			
			.def("setDirectional", &ofLight::setDirectional)
			.def("getIsDirectional", &ofLight::getIsDirectional)
			
			.def("setSpotlight", &lightSetSpotlight0)
			.def("setSpotlight", &lightSetSpotlight1)
			.def("setSpotlight", &ofLight::setSpotlight)
			.def("getIsSpotlight", &ofLight::getIsSpotlight)
			.def("setSpotlightCutOff", &ofLight::setSpotlightCutOff)
			.def("getSpotlightCutOff", &ofLight::getSpotlightCutOff)
			.def("setSpotConcentration", &ofLight::setSpotConcentration)
			.def("getSpotConcentration", &ofLight::getSpotConcentration)
			
			.def("setPointLight", &ofLight::setPointLight)
			.def("getIsPointLight", &ofLight::getIsPointLight)
			.def("setAttenuation", &lightSetAttenuation0)
			.def("setAttenuation", &lightSetAttenuation1)
			.def("setAttenuation", &ofLight::setAttenuation)
			.def("getAttenuationConstant", &ofLight::getAttenuationConstant)
			.def("getAttenuationLinear", &ofLight::getAttenuationLinear)
			.def("getAttenuationQuadratic", &ofLight::getAttenuationQuadratic)
			
			.def("getType", &ofLight::getType)
			
			.def("getAmbientColor", (ofColor(ofLight::*)(void)) &ofLight::getAmbientColor)
			.def("setAmbientColor", (void(ofLight::*)(ofColor&)) &ofLight::setAmbientColor)
			.def("setAmbientColor", &lightSetAmbientColor3)
			.def("setAmbientColor", &lightSetAmbientColor4)
			.def("setAmbientColor", &lightSetAmbientHexColor)
			.def("getDiffuseColor", (ofColor(ofLight::*)(void)) &ofLight::getDiffuseColor)
			.def("setDiffuseColor", (void(ofLight::*)(ofColor&)) &ofLight::setDiffuseColor)
			.def("setDiffuseColor", &lightSetDiffuseColor3)
			.def("setDiffuseColor", &lightSetDiffuseColor4)
			.def("setDiffuseColor", &lightSetDiffuseHexColor)
			.def("getSpecularColor", (ofColor(ofLight::*)(void)) &ofLight::getSpecularColor)
			.def("setSpecularColor", (void(ofLight::*)(ofColor&)) &ofLight::setSpecularColor)
			.def("setSpecularColor", &lightSetSpecularColor3)
			.def("setSpecularColor", &lightSetSpecularColor4)
			.def("setSpecularColor", &lightSetSpecularHexColor)
			
			.def("getLightID", &ofLight::getLightID)
			.def("customDraw", &ofLight::customDraw),
			
		///////////////////////////////
		/// \section ofMaterial.h
		
		class_<ofMaterial>("Material")
			.def(constructor<>())
			
			.def("setColors", &ofMaterial::setColors)
			
			.def("getDiffuseColor", &ofMaterial::getDiffuseColor)
			.def("setDiffuseColor", &ofMaterial::setDiffuseColor)
			.property("diffuseColor", &ofMaterial::getDiffuseColor, &ofMaterial::setDiffuseColor)
			
			.def("getAmbientColor", &ofMaterial::getAmbientColor)
			.def("setAmbientColor", &ofMaterial::setAmbientColor)
			.property("ambientColor", &ofMaterial::getAmbientColor, &ofMaterial::setAmbientColor)
			
			.def("getSpecularColor", &ofMaterial::getSpecularColor)
			.def("setSpecularColor", &ofMaterial::setSpecularColor)
			.property("specularColor", &ofMaterial::getSpecularColor, &ofMaterial::setSpecularColor)
			
			.def("getEmissiveColor", &ofMaterial::getEmissiveColor)
			.def("setEmissiveColor", &ofMaterial::setEmissiveColor)
			.property("emissiveColor", &ofMaterial::getEmissiveColor, &ofMaterial::setEmissiveColor)
			
			.def("getShininess", &ofMaterial::getShininess)
			.def("setShininess", &ofMaterial::setShininess)
			.property("shininess", &ofMaterial::getShininess, &ofMaterial::setShininess)
			
			.def("beginMaterial", &ofMaterial::begin)
			.def("endMaterial", &ofMaterial::end),
			
		///////////////////////////////
		/// \section ofShader.h
		
		class_<ofShader>("Shader")
			.def(constructor<>())
			.def(constructor<const ofShader&>())
			
			.def("load", (bool(ofShader::*)(string)) &ofShader::load)
			.def("load", &shaderLoad2)
			.def("load", (bool(ofShader::*)(string,string,string)) &ofShader::load)
			
			.def("setGeometryInputType", &ofShader::setGeometryInputType)
			.def("setGeometryOutputType", &ofShader::setGeometryOutputType)
			.def("setGeometryOutputCount", &ofShader::setGeometryOutputCount)
			.def("getGeometryMaxOutputCount", &ofShader::getGeometryMaxOutputCount)
			
			.def("unload", &ofShader::unload)
			.def("isLoaded", &ofShader::isLoaded)
			.property("loaded", &ofShader::isLoaded)
			
			.def("beginShader", &ofShader::begin)
			.def("endShader", &ofShader::end)
			
			.def("setUniformTexture", (void(ofShader::*)(const string&,ofBaseHasTexture&,int)) &ofShader::setUniformTexture)
			.def("setUniformTexture", (void(ofShader::*)(const string&,ofTexture&,int)) &ofShader::setUniformTexture)
			.def("setUniformTexture", (void(ofShader::*)(const string&,int,int,int)) &ofShader::setUniformTexture)
			
			.def("setUniform1i", &ofShader::setUniform1i)
			.def("setUniform2i", &ofShader::setUniform2i)
			.def("setUniform3i", &ofShader::setUniform3i)
			.def("setUniform4i", &ofShader::setUniform4i)
			
			.def("setUniform1f", &ofShader::setUniform1f)
			.def("setUniform2f", &ofShader::setUniform2f)
			.def("setUniform3f", &ofShader::setUniform3f)
			.def("setUniform4f", &ofShader::setUniform4f)
			
			// ignoring vector functions for now re. pointers
			
			.def("setUniformMatrix4f", &ofShader::setUniformMatrix4f)
			.def("getAttributeLocation", &ofShader::getAttributeLocation)
			
			.def("setAttribute1f", &ofShader::setAttribute1f)
			.def("setAttribute2f", &ofShader::setAttribute2f)
			.def("setAttribute3f", &ofShader::setAttribute3f)
			.def("setAttribute4f", &ofShader::setAttribute4f)
			
			.def("bindAttribute", &ofShader::bindAttribute)
			
			.def("printActiveUniforms", &ofShader::printActiveAttributes)
			.def("printActiveAttributes", &ofShader::printActiveAttributes)
			
			// ignoring advanced functions for now
			
			.def(self == other<const ofShader&>()),
			
		///////////////////////////////
		/// \section ofTexture.h
		
		def("getUsingArbTex", &ofGetUsingArbTex),
		def("enableArbTex", &ofEnableArbTex),
		def("disableArbTex", &ofDisableArbTex),
		
		def("getUsingNormalizedTexCoords", &ofGetUsingNormalizedTexCoords),
		def("enableNormalizedTexCoords", &ofEnableNormalizedTexCoords),
		def("disableNormalizedTexCoords", &ofDisableNormalizedTexCoords),
    
        def("setTextureWrapRepeat", &setTextureWrapRepeat0), //added
		def("setTextureWrap", &ofSetTextureWrap),
		def("getUsingCustomTextureWrap", &ofGetUsingCustomTextureWrap),
		def("restoreTextureWrap", &ofRestoreTextureWrap),
		
		def("setMinMagFilters", &setMinMagFilters0),
		def("setMinMagFilters", &setMinMagFilters1),
		def("setMinMagFilters", &ofSetMinMagFilters),
		def("getUsingCustomMinMag", &ofGetUsingCustomMinMagFilters),
		def("restoreMinMagFilters", &ofRestoreMinMagFilters),
		
		class_<TexCompression>("COMPRESS")
			.enum_("type") [
				value("NONE", OF_COMPRESS_NONE),
				value("SRGB", OF_COMPRESS_SRGB),
				value("ARB", OF_COMPRESS_ARB)
			],
    
    
			
		// ignoring texture edge hack functions
		
		class_<ofTexture>("Texture")
			.def(constructor<>())
			.def(constructor<const ofTexture&>())
			
			.def("allocate", (void(ofTexture::*)(int,int,int)) &ofTexture::allocate)
			.def("allocate", (void(ofTexture::*)(int,int,int,bool)) &ofTexture::allocate)
			.def("allocate", (void(ofTexture::*)(const ofPixels&)) &ofTexture::allocate)
			.def("clear", &ofTexture::clear)
			
			.def("setUseExternalTextureID", &ofTexture::setUseExternalTextureID)
			
			.def("loadData", (void(ofTexture::*)(const ofPixels&)) &ofTexture::loadData)
			
			.def("loadScreenData", &textureLoadScreenData0)
			.def("loadScreenData", &ofTexture::loadScreenData)
			
			.def("setAnchorPercent", &ofTexture::setAnchorPercent)
			.def("setAnchorPoint", &ofTexture::setAnchorPoint)
			.def("resetAnchor", &ofTexture::resetAnchor)
			
			.def("draw", (void(ofTexture::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofTexture::draw)
			.def("draw", (void(ofTexture::*)(float,float)) &ofTexture::draw)
			.def("draw", (void(ofTexture::*)(float,float,float)) &ofTexture::draw)
			.def("draw", (void(ofTexture::*)(float,float,float,float)) &ofTexture::draw)
			
			.def("drawSubsection", (void(ofTexture::*)(float,float,float,float,float,float)) &ofTexture::drawSubsection)
			.def("drawSubsection", (void(ofTexture::*)(float,float,float,float,float,float,float)) &ofTexture::drawSubsection)
			.def("drawSubsection", (void(ofTexture::*)(float,float,float,float,float,float,float,float)) &ofTexture::drawSubsection)
			.def("drawSubsection", (void(ofTexture::*)(float,float,float,float,float,float,float,float,float)) &ofTexture::drawSubsection)
			
			.def("readToPixels", (void(ofTexture::*)(ofPixels&)) &ofTexture::readToPixels)
    
            .def("bind", &bindTexture)
            .def("unbind", &unbindTexture)
			
			.def("getCoordFromPoint", &ofTexture::getCoordFromPoint)
			.def("getCoordFromPercent", &ofTexture::getCoordFromPercent)
			
			.def("setTextureWrap", &ofTexture::setTextureWrap)
            .def("setTextureWrapRepeat", &setTextureWrapRepeat1)
			.def("setTextureMinMagFilter", &ofTexture::setTextureMinMagFilter)
			
			.def("setCompression", &ofTexture::setCompression)
			
			.def("isAllocated", &ofTexture::isAllocated)
			.property("allocated", &ofTexture::isAllocated)
			
			.def("getType", &textureGetType)
			.property("type", &textureGetType)
			
			.def("getWidth",  &ofTexture::getHeight)
			.def("getHeight", &ofTexture::getHeight)
			.property("width",  &ofTexture::getHeight)
			.property("height", &ofTexture::getHeight)
			
			.property("flip", &textureGetFlip, &textureSetFlip)
			.property("tex_t", &textureGetTexT, &textureSetTexT)
			.property("tex_u", &textureGetTexU, &textureSetTexU)
			.property("tex_w", &textureGetTexW, &textureSetTexW)
			.property("tex_h", &textureGetTexH, &textureSetTexH)
    
            .scope[
                   //Use by of.Texture.WRAP.X
                   class_<TexWrapDummy>("WRAP")
                   .enum_("type") [
                                   value("CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE),
                     #ifdef GL_CLAMP_TO_BORDER
                                   value("CLAMP_TO_BORDER", GL_CLAMP_TO_BORDER),
                     #endif
                                   value("MIRRORED_REPEAT", GL_MIRRORED_REPEAT),
                                   value("REPEAT", GL_REPEAT)
                                 ]
            ]
   
      
			.enum_("textureType") [
				value("LUMINENCE", GL_LUMINANCE),
				value("RGB", GL_RGB),
				value("RGBA", GL_RGBA)
			],
			
		///////////////////////////////
		/// \section ofVbo.h
		
		class_<ofVbo>("Vbo")
			.def(constructor<>())
			.def(constructor<const ofVbo&>())
			
			// need some way to work out data passing using pointers
			//.def("setMesh", (void(ofVbo::*)(const ofMesh&,int)) &ofVbo::setMesh)
			//.def("setMesh", (void(ofVbo::*)(const ofMesh&,int,bool,bool,bool)) &ofVbo::setMesh)
			
            .def("addVertex", &addVertexVboMesh)
            .def("addColor", &addColorVboMesh)
            .def("addColor", &addColorAVboMesh)
            .def("addNormal", &addNormalVboMesh)
            .def("addIndex", &addIndexVboMesh)
            .def("addTexCoord", &addTexCoordVboMesh)
    
			.def("updateMesh", &ofVbo::updateMesh)
			
			.def("enableColors", &ofVbo::enableColors)
			.def("enableNormals", &ofVbo::enableNormals)
			.def("enableTexCoords", &ofVbo::enableTexCoords)
			.def("enableIndices", &ofVbo::enableIndices)
			
			.def("disableColors", &ofVbo::disableColors)
			.def("disableNormals", &ofVbo::disableNormals)
			.def("disableTexCoords", &ofVbo::disableTexCoords)
			.def("disableIndices", &ofVbo::disableIndices)
			
			.def("getVertId", &ofVbo::getVertId)
			.def("getColorId", &ofVbo::getColorId)
			.def("getNormalId", &ofVbo::getNormalId)
			.def("getTexCoordId", &ofVbo::getTexCoordId)
			.def("getIndexId", &ofVbo::getIndexId)
			
			.def("getIsAllocated", &ofVbo::getIsAllocated)
			.property("allocated", &ofVbo::getIsAllocated)
			
			.def("getUsingVerts", &ofVbo::getUsingVerts)
			.def("getUsingColors", &ofVbo::getUsingColors)
			.def("getUsingNormals", &ofVbo::getUsingNormals)
			.def("getUsingTexCoords", &ofVbo::getUsingTexCoords)
			.def("getUsingIndices", &ofVbo::getUsingIndices)
			
			.def("draw", &ofVbo::draw)
			.def("drawElements", &ofVbo::drawElements)
			
			.def("drawInstanced", &ofVbo::drawInstanced)
			.def("drawElementsInstanced", &ofVbo::drawElementsInstanced)
			
			.def("bind", &ofVbo::bind)
			.def("unbind", &ofVbo::unbind)
			
			.def("clear", &ofVbo::clear)
			.def("clearVertices", &ofVbo::clearVertices)
			.def("clearNormals", &ofVbo::clearNormals)
			.def("clearColors", &ofVbo::clearColors)
			.def("clearTexCoords", &ofVbo::clearTexCoords)
			.def("clearIndices", &ofVbo::clearIndices)
			
			.def("getNumVertices", &ofVbo::getNumVertices)
			.def("getNumIndices", &ofVbo::getNumIndices)
			
			.def("enableVAOS", &ofVbo::enableVAOs)
			.def("disableVAOS", &ofVbo::disableVAOs),
		
		///////////////////////////////
		/// \section ofVboMesh.h
		
		class_<ofVboMesh, ofMesh>("VboMesh")
			.def(constructor<>())
			.def(constructor<const ofVboMesh&>())
			.def("setUsage", &ofVboMesh::setUsage)
    
            .def("addVertex", &addVertexVboMesh)
            .def("addColor", &addColorVboMesh)
            .def("addColor", &addColorAVboMesh)
            .def("addNormal", &addNormalVboMesh)
            .def("addIndex", &addIndexVboMesh)
            .def("addTexCoord", &addTexCoordVboMesh)
			
			.def("enableColors", &ofVboMesh::enableColors)
			.def("enableTextures", &ofVboMesh::enableTextures)
			.def("enableNormals", &ofVboMesh::enableNormals)
			.def("enableIndices", &ofVboMesh::enableIndices)
			
			.def("disableColors", &ofVboMesh::disableColors)
			.def("disableTextures", &ofVboMesh::disableTextures)
			.def("disableNormals", &ofVboMesh::disableNormals)
			.def("disableIndices", &ofVboMesh::disableIndices)
			
			.def("usingColors", &ofVboMesh::usingColors)
			.def("usingTextures", &ofVboMesh::usingTextures)
			.def("usingNormals", &ofVboMesh::usingNormals)
			.def("usingIndices", &ofVboMesh::usingIndices)
			
            .scope[
                   //Use by of.VboMesh.PolyRenderMode.x
                   class_<ofPolyRenderMode>("PolyRenderMode")
                   .enum_("polyRenderMode") [
                           value("MESH_POINTS", OF_MESH_POINTS),
                           value("MESH_WIREFRAME", OF_MESH_WIREFRAME),
                           value("MESH_FILL", OF_MESH_FILL)
                           ]
           ]
    
			.def("draw",(void(ofVboMesh::*)(ofPolyRenderMode)) &ofVboMesh::draw)
			.def("drawInstanced", &ofVboMesh::drawInstanced)
			
			.def("getVbo", &ofVboMesh::getVbo),
    
        def("isGLProgrammableRenderer", &ofIsGLProgrammableRenderer)
	;
}

} // namespace
