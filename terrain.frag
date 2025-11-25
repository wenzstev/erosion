in vec3 vFragPos;
in vec3 vNormal;
in float vHeight;

// --- Output ---
out vec4 FragColor;

// --- Uniforms ---
uniform vec3 uViewPos; // Camera position

void main()
{
    // --- 1. Ambient Lighting ---
    float ambientStrength = 0.2;
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = ambientStrength * lightColor;

    // --- 2. Diffuse Lighting ---
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.5)); // A hard-coded sun direction
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // --- 3. Specular Lighting ---
    float specularStrength = 0.4;
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // --- 4. Color based on height ---
    // Simple gradient: low (dark green) to high (snowy white)
    vec3 lowColor = vec3(0.0, 0.3, 0.0);  // Dark Green
    vec3 highColor = vec3(1.0, 1.0, 1.0); // White
    float heightT = clamp(vHeight / 40.0, 0.0, 1.0); // Assuming 40 is max height
    vec3 terrainColor = mix(lowColor, highColor, heightT);

    // Combine lighting and terrain color
    vec3 result = (ambient + diffuse + specular) * terrainColor;
    FragColor = vec4(result, 1.0);
}