#version 120

uniform sampler2DRect tex;
uniform vec3 col;
uniform float thr;
uniform float alpha;
uniform int bPhoto;

void main(){
    vec2 tc = gl_TexCoord[0].st;
    vec4 texel = texture2DRect(tex, tc);
    float bgt = (texel.r+texel.g+texel.b)/3.0;
    if(bgt<thr){
        if(bPhoto==1){
            texel = vec4(col.r,col.g,col.b,alpha)*0.7 + texel*0.3;
        }else{
            texel = vec4(col.r,col.g,col.b,alpha);
        }
    }else{
        texel = vec4(0.0,0.0,0.0,0.0);
    }
    gl_FragColor = texel;
}
