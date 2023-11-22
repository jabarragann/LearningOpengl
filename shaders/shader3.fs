#version 330 core
// out vec4 gl_FragColor;

vec2 u_resolution = vec2(800.0, 600.0);
vec4 temp_color;

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution;
	temp_color = vec4(st.x,st.y,0.0,1.0);

    if(gl_FragCoord.x < u_resolution.x/2 && gl_FragCoord.y < u_resolution.y/2)
        gl_FragColor = temp_color;
    else if(gl_FragCoord.x > u_resolution.x/2 && gl_FragCoord.y > u_resolution.y/2)
        gl_FragColor = temp_color; 
    else
        gl_FragColor = vec4(0.0, 0.2, 0.0, 1.0);    
} 
