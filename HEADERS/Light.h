#pragma once
#include <windows.h>
#include <gl/GL.h>

//----------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------�WIAT�O--------------------------------------------------------																												
//------------------------------klasa definiuj�ca i inicjalizuj�ca �r�d�o �wiat�a w OpenGL------------------------------
//----------------------------------------------------------------------------------------------------------------------

//definicja parametr�w u�ywanych do okre�lenia �r�d�a �wiat�a
//kombinacja tych parametr�w okreslana jest do zdefiniowania zmiennej lightParams
//ka�demu parametrowi przypisany jest konkretny bit w s�owie lightParams
#define ambientLight					0x001
#define diffuseLight					0x002
#define specularLight					0x004
#define lightPosition					0x008
#define lightDirection					0x010
#define lightSpotExponent				0x020
#define lightSpotCutoff					0x040
#define lightConstantAttenuation		0x080
#define lightLinearAttenuation			0x100
#define lightQuadraticAttenuation		0x200

class Light {
	GLenum lightIdx;									//ozanczenie �r�d�a �wiat�a [GL_LIGHT0, ... , GL_LIGHT7] 
	unsigned int lightParams;							//parametry �r�d�a �wiat�a
	mutable bool enable;										//uruchomienie �r�d�a �wiat�a

	float position[4];									//pozycja �r�d�a �wiat�a
	float direction[3];									//kierunek wektora �r�d�a �wiat�a
	float ambientParams[4];								//parametry �wiat�a otoczenia
	float diffuseParams[4];								//parametry �wiat�a rozproszonego
	float specularParams[4];							//parametry �wiat�a odbicia
	float spotExponentParam;							//parametr koncentracji strumienia �wiat�a
	float spotCutoffParam;								//parametr k�ta rozwarcia strumienia �wiat�a
	float constantAttenuationParam;						//parametr sta�ej warto�ci t�umienia
	float linearAttenuationParam;						//parametr liniowej warto�ci t�umienia
	float quadraticAttenuationParam;					//parametr kwadratowej warto�ci t�umienia

public:
	Light();											//konstruktor domy�lny
	Light(GLenum LightIdx, unsigned int params);		//konstruktor rozszerzony [wczytuje od razu podstawowe parametry obiektu]

	//inicjalizacja w�a�ciwo�ci �r�d�a �wiat�a
	void Initialize() const;

	//usatwienie odpowiednich parametr�w �r�d�a �wiat�a
	void SetLightIdx(GLenum idx) { lightIdx = idx; }
	void SetLightParams(unsigned int params) { lightParams = params; }
	void SetPosition(float X, float Y, float Z);
	void SetDirection(float X, float Y, float Z);
	void SetAmbientParams(float R, float G, float B, float a);
	void SetDiffuseParams(float R,float G,float B,float a);
	void SetSpecularParams(float R, float G, float B, float a);
	void SetSpotExponentParam(float param) { spotExponentParam = param; }
	void SetSpotCutoffParam(float param) { spotCutoffParam = param; }
	void SetConstantAttenuationParam(float param) { constantAttenuationParam = param; }
	void SetLinearAttenuationParam(float param) { linearAttenuationParam = param; }
	void SetQuadraticAttenuationParam(float param) { quadraticAttenuationParam = param; }
	
	//w��czenie �r�d�a �wiat�a
	void EnableLight() const { glEnable(lightIdx); enable = true; }
	//wy��czenie �r�d�a �wiat�a
	void DisableLight() const { glDisable(lightIdx); enable = false; }

	bool IsEnabled() const { return enable; }					//sprawdzenie uruchomienia �r�d�a �wiat�a
};