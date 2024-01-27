#version 330 core

// out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // gl_FragColor = vec4(ourColor, 1.0); 
    gl_FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.5); // * vec4(ourColor, 1.0);

} 