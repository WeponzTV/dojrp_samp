#include <YSI_Coding\y_hooks>

stock GetObjectParameter(const string[], return_str[], delim, start_index)
{
	new x = 0;
	while(string[start_index] != EOS && string[start_index] != delim)
	{
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;

	if(string[start_index] == EOS) start_index = (-1);
	return start_index;
}

stock LoadObjectsFromFile(const file[])
{
	new File:handle, line[256], param[64], index, modelid, Float:pos[6];
	handle = fopen(file, filemode:io_read);
	if(!handle) return 0;

	while(fread(handle, line, sizeof(line)) > 0)
	{
	    index = 0;

  		index = GetObjectParameter(line, param, ',', index);
  		if(index == (-1)) continue;
  		modelid = strval(param);

  		index = GetObjectParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[0] = floatstr(param);

  		index = GetObjectParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[1] = floatstr(param);

  		index = GetObjectParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[2] = floatstr(param);

  		index = GetObjectParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[3] = floatstr(param);

  		index = GetObjectParameter(line, param, ',', index + 1);
  		if(index == (-1)) continue;
  		pos[4] = floatstr(param);

  		index = GetObjectParameter(line, param, ';', index + 1);
  		pos[5] = floatstr(param);
  		
  		CreateDynamicObject(modelid, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], -1, -1, -1, 250.0);
	}

	fclose(handle);
	return 1;
}

hook OnGameModeInit()
{
	LoadObjectsFromFile("DOJRP/objects/ls.txt");
	LoadObjectsFromFile("DOJRP/objects/sf.txt");
	LoadObjectsFromFile("DOJRP/objects/lv.txt");
	return 1;
}
