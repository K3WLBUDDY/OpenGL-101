#include "DShader.h"

DShader::DShader() : _vs(0), _fs(0), pid(0){}

bool DShader::compileShader(const string& filePath)
{
  ifstream shaderCode(filePath);
  if(shaderCode.fail())
  {
    perror(filePath.c_str());
    std::cout<<"\n Failed to Open " <<filePath;

    return false;
  }
  string code="";
  string line;

  int pathLen = strlen(filePath);
  int extBuffer = pathLen-2;
  string ext[2];

  for(int i=0;i<2;i++)
    strcpy(ext[i], filePath[extBuffer++]);

  if(strcmp(ext, "vs") == 0)
  {
    _vs = glCreateShader(GL_VERTEX_SHADER);

    if(_vs == 0)
    {
       std::cout<<"\n Failed to Create Vertex Shader";
       return false;
    }

    else
    {
      while(getline(shaderCode, line))
      {
        code += line+"\n";
      }
      shaderCode.close();

      const char* contentPtr = code.c_str();

      glShaderSource(_vs, 1, &contentPtr, nullptr);
      glCompileShader(_vs);

      GLint success =0;

      glGetShaderiv(_vs, GL_COMPILE_STATUS, &success);

      if(success == GL_FALSE)
      {
        GLint maxLen=0;
        glGetShaderiv(_vs, GL_INFO_LOG_LENGTH, &maxLen);

        vector<char> errorLog(maxLen);
        glGetShaderInfoLog(_vs, maxLen, &maxLen, &errorLog[0]);

        glDeleteShader(_vs);

        printf("\n%s", &errorLog[0]);

        std::cout<<"\n Failed to Compile Vertex Shader";

        SDL_Quit();
      }
    }


  }
  else if(strcmp(ext, "fs") == 0)
  {
    _fs = glCreateShader(GL_FRAGMENT_SHADER);

    if(_fs == 0)
    {
       std::cout<<"\n Failed to Create Fragment Shader";
       return false;
    }

    else
    {
      while(getline(shaderCode, line))
      {
        code += line+"\n";
      }
      shaderCode.close();

      const char* contentPtr = code.c_str();

      glShaderSource(_fs, 1, &contentPtr, nullptr);
      glCompileShader(_fs);

      GLint success =0;

      glGetShaderiv(_fs, GL_COMPILE_STATUS, &success);

      if(success == GL_FALSE)
      {
        GLint maxLen=0;
        glGetShaderiv(_fs, GL_INFO_LOG_LENGTH, &maxLen);

        vector<char> errorLog(maxLen);
        glGetShaderInfoLog(_fs, maxLen, &maxLen, &errorLog[0]);

        glDeleteShader(_fs);

        printf("\n%s", &errorLog[0]);

        std::cout<<"\n Failed to Compile Fragment Shader";

        SDL_Quit();
      }
  }
}

bool DShader::linkShader()
{

  _pID = glCreateProgram();
  //Attach our shaders to our program
	glAttachShader(_pID, _vs);
	glAttachShader(_pID, _fs);

	//Link our program
	glLinkProgram(_pID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_pID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_pID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_pID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_pID);
		//Don't leak shaders either.
		glDeleteShader(_vs);
		glDeleteShader(_fs);


		//Use the infoLog as you see fit.
		printf("%s\n", &(infoLog[0]));
		fatalError("Shader failed to Link");

}

void DShader::use()
{

}

void DShader::unuse()
{

}
