#include "Light.h"

//konstruktor domy�lny
Light::Light() :position{ 0 }, direction{ 0 }, ambientParams{ 0 }, diffuseParams{ 0 }, specularParams{ 0 }{
	lightIdx = GL_LIGHT0;																//pierwsze �r�d�o �wiat�a
	lightParams = 0;																	//brak parametr�w
	enable = false;																		//�r�d�o wy��czone

	//zainicjalizowanie wszystkich parametr�w �r�d�a �wiat�a warto�ciami domy�lnymi
	//position[4] = { 0 };
	//direction[3] = { 0 };
	//ambientParams[4] = { 0 };
	//diffuseParams[4] = { 0 };
	//specularParams[4] = { 0 };
	spotExponentParam = 0.0;
	spotCutoffParam = 0.0;
	constantAttenuationParam = 0.0;
	linearAttenuationParam = 0.0;
	quadraticAttenuationParam = 0.0;
}

//konstruktor rozszerzony [wczytuje podstawowe parametry obiektu od razu przy tworzeniu]
Light::Light(GLenum LightIdx, unsigned int params) :position{ 0 }, direction{ 0 }, ambientParams{ 0 }, diffuseParams{ 0 }, specularParams{ 0 } {
	lightIdx = LightIdx;																//indeks �r�d�a �wiat�a [LIGHT0, ... , LIGHT7]
	lightParams = params;																//parametry �r�d�a �wiat�a
	enable = false;																		//�r�d�o wy��czone

	//zainicjalizowanie wszystkich parametr�w �r�d�a �wiat�a warto�ciami domy�lnymi
	//position[4] = { 0 };
	//direction[3] = { 0 };
	//ambientParams[4] = { 0 };
	//diffuseParams[4] = { 0 };
	//specularParams[4] = { 0 };
	spotExponentParam = 0.0;
	spotCutoffParam = 0.0;
	constantAttenuationParam = 0.0;
	linearAttenuationParam = 0.0;
	quadraticAttenuationParam = 0.0;
}

//zainicjalizowanie �r�d�a �wiat�a w OpenGL
void Light::Initialize() const{
	//w zale�no�ci od warto�ci konkretnych bit�w w zmiennej lightParams inicjalizujemy konkretne parametry �r�d�a �wiat�a
	if (lightParams & ambientLight)
		glLightfv(lightIdx, GL_AMBIENT, ambientParams);									//intensywno�� �wiat�a otoczenia
	if (lightParams & diffuseLight)
		glLightfv(lightIdx, GL_DIFFUSE, diffuseParams);									//intensywno�� �wiat�a rozproszonego
	if (lightParams & specularLight)			
		glLightfv(lightIdx, GL_SPECULAR, specularParams);								//intensywno�� �wait�a odbicia
	if (lightParams & lightPosition)
		glLightfv(lightIdx, GL_POSITION, position);										//pozycja �r�d�a �wiat�a
	if (lightParams & lightDirection)
		glLightfv(lightIdx, GL_SPOT_DIRECTION, direction);								//wektor kierunku �r�d�a �wiat�a
	if (lightParams & lightSpotExponent)
		glLightf(lightIdx, GL_SPOT_EXPONENT, spotExponentParam);						//koncentracja strumienia �wiat�a
	if (lightParams & lightSpotCutoff)
		glLightf(lightIdx, GL_SPOT_CUTOFF, spotCutoffParam);							//k�t rozwarcia strumienia �wiat�a
	if (lightParams & lightConstantAttenuation)
		glLightf(lightIdx, GL_CONSTANT_ATTENUATION, constantAttenuationParam);			//sta�a warto�� t�umienia
	if (lightParams & lightLinearAttenuation)
		glLightf(lightIdx, GL_LINEAR_ATTENUATION, linearAttenuationParam);				//liniowa warto�� t�umienia
	if (lightParams & lightQuadraticAttenuation)
		glLightf(lightIdx, GL_QUADRATIC_ATTENUATION, quadraticAttenuationParam);		//kwadratowa warto�� t�umienia
}

//ustawienie pozycji �r�d�a �wiat�a
void Light::SetPosition(float X, float Y, float Z) {
	position[0] = X;
	position[1] = Y;
	position[2] = Z;
	position[3] = 1.0;
}

//ustawienie kierunku strumienia �wiat�a
void Light::SetDirection(float X, float Y, float Z) {
	direction[0] = X;
	direction[1] = Y;
	direction[2] = Z;
}

//ustaweinie intensywno�ci �wiat�a otoczenia
void Light::SetAmbientParams(float R, float G, float B, float a) {
	ambientParams[0] = R;
	ambientParams[1] = G;
	ambientParams[2] = B;
	ambientParams[3] = a;
}

//ustawienie intensywno�ci �wiat�a rozproszonego
void Light::SetDiffuseParams(float R, float G, float B, float a) {
	diffuseParams[0] = R;
	diffuseParams[1] = G;
	diffuseParams[2] = B;
	diffuseParams[3] = a;
}

//ustwienie intesywno�ci �wiat�a odbicia
void Light::SetSpecularParams(float R, float G, float B, float a) {
	specularParams[0] = R;
	specularParams[1] = G;
	specularParams[2] = B;
	specularParams[3] = a;
}