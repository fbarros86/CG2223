#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


float radius, slices, stacks, length, divs, height;

void plane(float size,float divs,char * file){
    std::ofstream outfile;
    outfile.open(file);
    float x = -size/2;
	float z;
	for (int i = 0; i <= divs; i++) {
		z=size/2;
		for (int j = 0; j <= divs; j++){
            outfile << x << " " << 0.0f << " " << z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
            outfile << (float)i/(float)divs << " " << (float)j/(float)divs << " ";
			z -= size / divs;
		}
		x += size / divs;
	}
    outfile << "\n";
    for (int i = 0; i < divs; i++) {
        for (int j = 0; j < divs; j++){
            int p1,p2,p3,p4;
            p1=i*(divs+1) + j;
            p2=i*(divs+1) + (j+1);
            p3=(i+1)*(divs+1) + j;
            p4=(i+1)*(divs+1) + j + 1 ;

            //Triangulo 1
            outfile << p1 << " " << p3 << " " << p2 << " ";
            //Triangulo 2
            outfile << p4 << " " << p2 << " " << p3 << " ";

        }
    }
    outfile.flush();
    outfile.close();
}

void box(float len, float divs,char * file){
    std::ofstream outfile;
    outfile.open(file);
    float x = -len / 2,z;

	for (int i = 0; i <= divs; i++) {
		z = len / 2;
		for (int j = 0; j <= divs; j++) {

			//TOPG
            outfile << x << " " << len/2 << " " << z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
            outfile << (float)i/divs << " " << 1.0f - (float)j/divs << " ";
			//face1
            outfile << len/2 << " " << x << " " << z << " ";
            outfile << 1.0f << " " << 0.0f << " " << 0.0f << " ";
            outfile << 1.0f - (float)(j)/divs << " " << (float)i/divs << " ";
			//face2
            outfile << -len/2 << " " << x << " " << z << " ";
            outfile << -1.0f << " " << 0.0f << " " << 0.0f << " ";
            outfile << 1.0f - (float)j/divs << " " << (float)i/divs << " ";
            //face3
            outfile <<  x << " " << z << " " << len / 2 << " ";
            outfile << 0.0f << " " << 0.0f << " " << 1.0f << " ";
            outfile << (float)(i)/divs << " " <<  1.0f - (float)(j)/divs << " ";
            // face4
            outfile << x << " " << z << " " << -len / 2 << " ";
            outfile << 0.0f << " " << 0.0f << " " << -1.0f << " ";
            outfile << (float)(i)/divs << " " <<  1.0f - (float)(j)/divs << " ";
			//BASED
            outfile << x << " " << - len / 2 << " " << z << " ";
            outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
            outfile << (float)(i)/divs << " " <<  1.0f - (float)(j)/divs << " ";


			
			z -= len / divs;
		}
		x += len / divs;
	}
    outfile << "\n";
    for (int i = 0; i < divs; i++) {
		for (int j = 0; j < divs; j++) {
            for (int k = 0; k < 6; k++) {
                int p1, p2, p3, p4;
                p1= i*6*(divs+1) + j*6 + k;
                p2= i*6*(divs+1) + (j+1)*6 + k;
                p3= (i+1)*6*(divs+1) + j*6 + k;
                p4= (i+1)*6*(divs+1) + (j+1)*6 + k;
                if(k%2 == 1){
                    //Traingulo 1
                    outfile << p1 << " " << p2 << " " << p3 << " ";
                    //Triangulo 2
                    outfile << p4 << " " << p3 << " " << p2 << " ";

                }else{
                    //Traingulo 1
                    outfile << p1 << " " << p3 << " " << p2 << " ";
                    //Triangulo 2
                    outfile << p4 << " " << p2 << " " << p3 << " ";
                }
                
            }

        }
    }
    outfile.flush();
    outfile.close();
    
}

void invertedBox(float len, float divs,char * file){
    std::ofstream outfile;
    outfile.open(file);
    float x = -len / 2,z;

	for (int i = 0; i <= divs; i++) {
		z = len / 2;
		for (int j = 0; j <= divs; j++) {

			//TOPG
            outfile << x << " " << len/2 << " " << z << " ";
            outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
            outfile << (float)i/divs << " " << 1.0f - (float)j/divs << " ";
			//face1
            outfile << len/2 << " " << x << " " << z << " ";
            outfile << -1.0f << " " << 0.0f << " " << 0.0f << " ";
            outfile << 1.0f - (float)(j)/divs << " " << (float)i/divs << " ";
			//face2
            outfile << -len/2 << " " << x << " " << z << " ";
            outfile << 1.0f << " " << 0.0f << " " << 0.0f << " ";
            outfile << 1.0f - (float)j/divs << " " << (float)i/divs << " ";
            //face3
            outfile <<  x << " " << z << " " << len / 2 << " ";
            outfile << 0.0f << " " << 0.0f << " " << -1.0f << " ";
            outfile << (float)(i)/divs << " " <<  1.0f - (float)(j)/divs << " ";
            // face4
            outfile << x << " " << z << " " << -len / 2 << " ";
            outfile << 0.0f << " " << 0.0f << " " << 1.0f << " ";
            outfile << (float)(i)/divs << " " <<  1.0f - (float)(j)/divs << " ";
			//BASED
            outfile << x << " " << - len / 2 << " " << z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
            outfile << (float)(i)/divs << " " <<  1.0f - (float)(j)/divs << " ";


			
			z -= len / divs;
		}
		x += len / divs;
	}
    outfile << "\n";
    for (int i = 0; i < divs; i++) {
		for (int j = 0; j < divs; j++) {
            for (int k = 0; k < 6; k++) {
                int p1, p2, p3, p4;
                p1= i*6*(divs+1) + j*6 + k;
                p2= i*6*(divs+1) + (j+1)*6 + k;
                p3= (i+1)*6*(divs+1) + j*6 + k;
                p4= (i+1)*6*(divs+1) + (j+1)*6 + k;
                if(k%2 == 1){
                    //Traingulo 1
                    outfile << p1 << " " << p3 << " " << p2 << " ";
                    //Triangulo 2
                    outfile << p4 << " " << p2 << " " << p3 << " ";

                }else{
                    //Traingulo 1
                    outfile << p1 << " " << p2 << " " << p3 << " ";
                    //Triangulo 2
                    outfile << p4 << " " << p3 << " " << p2 << " ";
                }
                
            }

        }
    }
    outfile.flush();
    outfile.close();
    
}



void sphere(float radius, float slices, float stacks,char * file) {
    std::ofstream outfile;
    outfile.open(file);
	float a = 0, b = -(M_PI/2), y;
	for (int i = 0; i <= stacks;i++) {
		a = 0;
		y = radius * sin(b);
		for (int j = 0; j <= slices; j++) {

            outfile << radius *cos(b)*sin(a) << " " << y << " " << radius*cos(b)*cos(a) << " ";
            outfile << cos(b)*sin(a) << " " << y << " " << cos(b)*cos(a) << " ";
            outfile << (float)j/(float)slices << " " << (float)i/(float)stacks << " ";

			a += ((2 * M_PI) / slices);
		}
		b += (M_PI / stacks);
	}

    outfile << "\n";
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++){
            int p1,p2,p3,p4;
            p1=(slices +1)*i +j;
            p2=(slices +1)*i +j+1;
            p3=(slices +1)*(i+1) +j;
            p4=(slices +1)*(i+1) +j+1;
        
            //Triangulo 1 
            outfile << p1 << " " << p2 << " " << p3 << " ";
            //Triangulo 2
            outfile << p4 << " " << p3 << " " << p2 << " ";

        }
    }
    outfile.flush();
    outfile.close();

}


void cone(float radius, float height, float slices, float stacks,char * file){
    std::ofstream outfile;
    outfile.open(file);
    //BASE
    outfile << 0 << " " << 0 << " " << 0 << " ";	
    outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
    outfile << 0.5f << " " << 0<< " ";
	for (int k = 0;k <= slices;k++) {
        outfile << radius*sin(k*((2*M_PI)/slices)) << " " << 0 << " " << radius*cos(k * ((2 * M_PI) / slices)) << " ";
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << sin(k*((2*M_PI)/slices)) << " " << 0 << " ";
	}
	//RESTO
    float a = (atan(radius/height));
	float y=0 , r=radius;
	for (int i = 0; i <=stacks; i++) {
		for (int j = 0;j <= slices;j++) {
            float ang = j * ((2 * M_PI) / slices);
            outfile << r * sin(ang) << " " << y << " " << r * cos(ang) << " ";
            outfile << sin(ang)* cos(a) << " " << sin(a) << " " << cos(a) * cos(ang) << " ";
            outfile << (float)j/stacks << " " << (float)i/stacks << " ";
		}
		r -= (radius/ stacks);
		y += height / stacks;
	}
        outfile << "\n";
    for (int j = 0; j < slices; j++){
            int p1,p2,p3,p4,p5,p6,p7,p8;
            p1=0;
            p2=j+1;
            p3=j+2;
            outfile << p3 << " " << p2 << " " << p1 << " ";
    }
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++){
            int p1,p2,p3,p4;
            p1=slices+2 + (slices+1)*i + j;
            p2=slices+2 + (slices+1)*i + j+1;
            p3=slices+2 + (slices+1)*(i+1) + j;
            p4=slices+2 + (slices+1)*(i+1) + j+1;
        
            //Triangulo 1 
            outfile << p1 << " " << p2 << " " << p3 << " ";
            //Triangulo 2
            outfile << p4 << " " << p3 << " " << p2 << " ";

        }
    }
    
    outfile.flush();
    outfile.close();
    
}

void cylinder(float height, float radius, int sides, char * file){
    std::ofstream outfile;
    outfile.open(file);
    //build cilinder and its normals
    int vertex = 0;
	float delta = 2.0f * M_PI / sides;

    outfile << 0.0f << " " << height /2.0f << " " << 0.0f << " ";
    outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
    outfile << 0.4375f << " " << 0.1875f << " ";


    outfile << 0.0f << " " << -height / 2.0f << " " << 0.0f << " ";
    outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
    outfile << 0.8125 << " " << 0.1875 << " ";

	for (int i = 0; i <= sides; ++i) {
        //cima
        outfile << radius * sin( i * delta) << " " << height /2.0f << " " << radius * cos( i * delta) << " ";
        outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
        outfile << 0.4375 + (0.1875 * sin(i * delta)) << " " << 0.1875 + (0.1875 * cos(i * delta)) << " ";

        // baixo
        outfile << radius * sin( i * delta) << " " << -height / 2.0f << " " << radius * cos( i * delta) << " ";
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << 0.8125 + (0.1875 * sin((i+1) * delta)) << " " << 0.1875 + (0.1875 * cos((i+1) * delta)) << " ";

        //cima lateral
        outfile << radius * sin( i * delta) << " " << height /2.0f << " " << radius * cos( i * delta) << " ";
        outfile << sin(i*delta) << " " << 0.0f << " " << cos(i*delta) << " ";
        outfile << i/(float)sides<< " " << 1<< " ";

        //baixo lateral
        outfile << radius * sin( i * delta) << " " << -height/2.0f << " " << radius * cos( i * delta) << " ";
        outfile << sin (i * delta) << " " << 0.0f << " " << cos( i * delta) << " ";
        outfile << i/(float)sides<< " " << 0.375f << " ";

	}

    outfile << "\n";
    for (int i = 0; i < sides; i++) {
            int p1,p2,p3,p4,p5,p6,p7,p8;
            p1=2+i*4;//cima i
            p2=2+i*4 +1;//baixo 1
            p3=2+(i+1)*4;// cima i+1
            p4=2+(i+1)*4 +1;//baixo i+1
            p5=2+i*4+2;//cima lateral i
            p6=2+i*4+3;//baixo lateral i
            p7=2+(i+1)*4 +2;//cima lateral i+1
            p8=2+(i+1)*4 +3;//baixo lateral i+1
            //Based
            outfile << 1 << " " << p4 << " " << p2 << " ";
            //TOPG
            outfile << 0 << " " << p1 << " " << p3 << " ";
            //Triangulo 1
            outfile << p5 << " " << p6 << " " << p7 << " ";
            //Triangulo 2
            outfile << p8 << " " << p7 << " " << p6 << " ";

    }
    
    outfile.flush();
    outfile.close();
}


void flatRing( float inner, float outer, int sides,int stacks, char * file){
    std::ofstream outfile;
    outfile.open(file);
    for(int i=0; i<=stacks; i++){
        for(int j=0; j<=sides;j++){
            float r = inner + i*(outer-inner)/(float)stacks;
            float x = cos(j*2.0f * M_PI / (float)sides);
            float z = sin(j*2.0f * M_PI / (float)sides);

            outfile << r*x << " " << 0.0f << " " << r*z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
            outfile << (float)i/(float)stacks << " " << (float)j << " " ;

        }
    }
    outfile << "\n";
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < sides; j++){
            int p1,p2,p3,p4;
            p1=i*(sides+1) + j;
            p2=i*(sides+1) + (j+1);
            p3=(i+1)*(sides+1) + j;
            p4=(i+1)*(sides+1) + j + 1 ;

            //Triangulo 1 - Cima
            outfile << p1 << " " << p3 << " " << p2 << " ";
            //Triangulo 2 - Cima
            outfile << p4 << " " << p2 << " " << p3 << " ";
            //Triangulo 1 - Baixo
            outfile << p1 << " " << p2 << " " << p3 << " ";
            //Triangulo 2 - Baixo
            outfile << p4 << " " << p3 << " " << p2 << " ";

        }
    }


    outfile.flush();
    outfile.close();

}

void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void multVectorMatrix(float *v, float *m, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[k*4+j];
		}
	}

}

float multVectorVector(float *v1, float *v2) {
    float r=0;
	for (int j = 0; j < 4; ++j) {
		r+=v1[j]*v2[j];
	}
    return r;

}



void getBezierPoint(float u, float v, float **points, float *pos,float*du,float*dv) {
    float m[4][4] = {{-1, 3, -3, 1},
                   {3, -6, 3, 0},
                   {-3, 3, 0, 0},
                   {1, 0, 0, 0}};

    float U[4] = {u * u * u, u * u, u, 1};
    float V[4] = {v * v * v, v * v, v, 1};
    float DV[4] = {3 * v * v, 2 * v, 1, 0};
    float DU[4] = {3 * u * u, 2 * u, 1, 0};

    float Ps[3][16];
    for(int i=0;i<16;i++){
        Ps[0][i]=points[i][0];
        Ps[1][i]=points[i][1];
        Ps[2][i]=points[i][2];
    }
    // Compute A = U * M for each component (x, y, z)
    // Compute B = U * M * P for each component (x, y, z)
    // Compute B = U * M * P * M for each component (x, y, z)
    // Compute B = U * M * P * M * V for each component (x, y, z)
	float A[4];
	float B[4];
    float AU[4];
    float BU[4];
	for (int i = 0; i < 3; i++) {
		multVectorMatrix(U,m[0], A);
        multVectorMatrix(A,Ps[i],B);
        multVectorMatrix(B,m[0],A);
        multVectorMatrix(DU,m[0], AU);
        multVectorMatrix(AU,Ps[i],BU);
        multVectorMatrix(BU,m[0],AU);
        pos[i] = multVectorVector(A,V);
        du[i] = multVectorVector(AU,V);
        dv[i]= multVectorVector(A,DV);
	}
} 

void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}



void patch(char* patch_file, int level, char* file){
    std::ifstream patch(patch_file);
    std::ofstream outfile;
    outfile.open(file);
    int num_patches;
    patch >> num_patches;
    int indexes[num_patches][16];
    for(int i=0; i<num_patches;i++){
        for(int j=0;j<16;j++){
            std:: string aux;
            patch >> aux;
            indexes[i][j]= std::stoi(aux);
        }
    }
    int num_control=0;
    patch >> num_control;
    float points[num_control][3];
    for(int i=0; i<num_control;i++){
        std:: string x,y,z;
        patch >> x >> y >> z;
        points[i][0]=std::stof(x);;
        points[i][1]=std::stof(y);;
        points[i][2]=std::stof(z);;
    }
    patch.close();
    for(int i=0;i<num_patches;i++){
        float *patch_points[16];
        for(int j=0;j<16;j++){
            patch_points[j]=points[indexes[i][j]];
        }
        for(int u=0;u<=level;u++)
            for(int v=0;v<=level;v++){
                float pos[3],du[3],dv[3],normal[3];
                getBezierPoint(u/(float)level,v/(float)level,patch_points,pos,du,dv);
                cross(dv,du,normal);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                outfile << normal[0] << " " << normal[1] << " " << normal[2] << " ";
                outfile << (float)u/level << " " << (float)v/level << " ";
            
            }
    }
    outfile << "\n";

    for(int i=0;i<num_patches;i++){
        float *patch_points[16];
        for(int j=0;j<16;j++){
            patch_points[j]=points[indexes[i][j]];
        }
        for(int u=0;u<level;u++)
            for(int v=0;v<level;v++){
                int p1,p2,p3,p4;
                p1=(level+1)*(level+1)*i + (level+1)*u + v;
                p2=(level+1)*(level+1)*i + (level+1)*u + v +1;
                p3=(level+1)*(level+1)*i + (level+1)*(u+1) + v;
                p4=(level+1)*(level+1)*i + (level+1)*(u+1) + v +1;

                //Triangulo 1 
                outfile << p1 << " " << p2 << " " << p3 << " ";
                //Triangulo 2
                outfile << p4 << " " << p3 << " " << p2 << " ";
            
            }
    }
    
    outfile.flush();
    outfile.close();
    

    
}


int main(int argc, char** argv) {
    std::string shape = argv[1];

	if (shape == "plane")  plane(std::stoi(argv[2]),std::stoi( argv[3]),argv[4]);
	else if (shape == "box") box(std::stoi(argv[2]),std::stoi( argv[3]),argv[4]);
	else if (shape == "skybox") invertedBox(std::stoi(argv[2]),std::stoi( argv[3]),argv[4]);
	else if (shape == "sphere") sphere(std::stoi(argv[2]),std::stoi( argv[3]),std::stoi(argv[4]),argv[5]);
	else if (shape == "cone") cone(std::stoi(argv[2]),std::stoi( argv[3]),std::stoi(argv[4]),std::stoi(argv[5]),argv[6]);
    else if (shape == "cylinder") cylinder(std::stoi(argv[2]),std::stoi( argv[3]),std::stoi(argv[4]),argv[5]);
    else if (shape == "ring") flatRing(std::stof(argv[2]),std::stof(argv[3]),std::stoi(argv[4]),std::stoi(argv[5]),argv[6]);
    else if (shape=="patch") patch(argv[2],std::stoi(argv[3]),argv[4]);//generator patch teapot.patch 10 bezier_10.3d
	else {
		std::cout << "Erro: Figura não suportada";
		return 1;
	}
    return 0;
}