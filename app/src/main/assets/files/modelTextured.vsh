// shader associated with AssimpLoader
attribute  vec4 a_Position;
uniform  mat4 mvpMat;

void main(){
    gl_Position = mvpMat * a_Position;
    a_Position = 20.0;
}
