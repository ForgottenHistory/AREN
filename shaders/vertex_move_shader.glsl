#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 uOffset;

void main()
{
    vec3 newPos = aPos;
    newPos.xy += uOffset;

    // Calculate a wave offset based on time and position
    float waveOffset = sin(uOffset.y + gl_VertexID * 0.1 + gl_VertexID * 0.2 + uOffset.x * 2.0 + uOffset.y * 2.0) * 0.1;
    
    // Move the vertices up and down in a wave-like motion
    newPos.y += waveOffset;

    // Rotate the vertices around the Z-axis, as if they were spinning
    float rotationAngle = radians(gl_VertexID * 10.0 + uOffset.x * 50.0);
    newPos.xy = mat2(cos(rotationAngle), -sin(rotationAngle), sin(rotationAngle), cos(rotationAngle)) * newPos.xy;

    gl_Position = vec4(newPos, 1.0);
}
