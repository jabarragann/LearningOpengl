#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

// Plot a line on Y using a value between 0.0-1.0
float plot(vec2 st, float pct){
  return  smoothstep( pct-0.02, pct, st.y) -
          smoothstep( pct, pct+0.02, st.y);
}

void main() {
	vec2 st = gl_FragCoord.xy/u_resolution; // Normalized coordinates

    // float y = st.x;
    // float y = pow(st.x,5.0);
    // float y = smoothstep(0.4,0.7,st.x);
    // float y = smoothstep(0.2,0.5,st.x) - smoothstep(0.5,0.8,st.x);
    float y = sin(st.x*6.28*4.0+u_time)/2.0 + 0.5; // Moving sine wave
    // float y = fract(sin(st.x*6.28*2.0))/1.5 + 0.25;
    // float y = ceil(st.x*8.0)/8.0; 

    vec3 color = vec3(y);
    // vec3 color = vec3(0.0);

    // Plot a line
    float pct = plot(st,y);
    color = (1.0-pct)*color+pct*vec3(1.0,0.0,0.0);

	gl_FragColor = vec4(color,1.0);
}