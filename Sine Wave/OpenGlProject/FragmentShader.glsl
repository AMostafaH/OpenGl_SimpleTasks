#version 330

in vec4 fragment_color;
void main()
{
	gl_FragColor = fragment_color;
	//gl_FragColor = vec4(0,1,0,1); //used to assign green color for the whole shape

}