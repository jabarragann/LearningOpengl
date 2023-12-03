#version 330 core
// out vec4 gl_FragColor;

uniform ivec2 u_resolution;
uniform float u_time;
vec4 grad_color;

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution;
	grad_color = vec4(st.x,st.y,0.0,1.0);

    if(gl_FragCoord.x < u_resolution.x/2 && gl_FragCoord.y < u_resolution.y/2)
        gl_FragColor = grad_color;
    else if(gl_FragCoord.x > u_resolution.x/2 && gl_FragCoord.y > u_resolution.y/2)
        gl_FragColor = grad_color; 
    else if(gl_FragCoord.x < u_resolution.x/2 && gl_FragCoord.y > u_resolution.y/2)
    {
        float green_value = abs(sin(u_time));
        gl_FragColor = vec4(0.0, green_value, 0.0, 1.0);    
    }
    else
    {
        float green_value = sin(u_time) / 2.0f + 0.5f;
        gl_FragColor = vec4(0.0, green_value, 0.0, 1.0);    
    }
} 
