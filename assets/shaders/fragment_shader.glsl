// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;
uniform float deceased;

void main()
{
    // Sample texture
    vec4 color = texture2D(onetex, uv_interp);

    // Assign color to fragment
    gl_FragColor = vec4(color.r, color.g, color.b, color.a);
    // Check for transparency

    if(deceased == 1) {
        float gray = (color.r + color.g + color.b) / 3.0;
        gl_FragColor = vec4(vec3(gray), 1.0);
    }

    if(color.a < 1.0)
    {
         discard;
    }
}