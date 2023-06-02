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
            for (int k = 0; j < 6; j++) {
                int p1, p2, p3, p4;
                p1= i*6*(divs+1) + j*6 + k;
                p2= i*6*(divs+1) + (j+1)*6 + k;
                p3= (i+1)*6*(divs+1) + j*6 + k;
                p4= (i+1)*6*(divs+1) + (j+1)*6 + k;
                //Traingulo 1
                outfile << p1 << " " << p3 << " " << p2 << " ";
                //Triangulo 2
                outfile << p4 << " " << p2 << " " << p3 << " ";


            }

        }
    }
    outfile.flush();
    outfile.close();
    
}


void sphere(float radius, float slices, float stacks,char * file) {
    std::ofstream outfile;
    outfile.open(file);
	float next_a, next_b, a = 0, b = 0, y, next_y;
	for (int i = 0; i <= stacks / 2;i++) {
		a = 0;
		next_b = b + (M_PI / stacks);
		y = radius * sin(b);
		next_y = radius * sin(next_b);
		for (int j = 0; j <= slices; j++) {
			next_a = a + ((2 * M_PI) / slices);

            outfile << radius *cos(b)*sin(a) << " " << y << " " << radius*cos(b)*cos(a) << " ";
            outfile << cos(b)*sin(a) << " " << y << " " << cos(b)*cos(a) << " ";
            outfile << (float)j/(float)slices << " " << 0.5f + ((float)i/(float)stacks)/2.0f << " ";

            outfile << radius * cos(b) * sin(a) << " " << - y << " " <<  radius * cos(b) * cos(a) << " ";
            outfile << cos(b) * sin(a) << " " << - y << " " <<  cos(b) * cos(a) << " ";
            outfile << (float)(j)/(float)slices << " " << (1 - (float)(i)/(float)stacks)/2 << " ";

			
			a = next_a;
		}
		y = next_y;
		b = next_b;
	}

    outfile << "\n";
    for (int i = 0; i < stacks/2; i++) {
        for (int j = 0; j < slices; j++){
            int p1,p2,p3,p4,p5,p6,p7,p8;
            p1=2*(slices +1)*i +j*2;
            p2=2*(slices +1)*i +(2*(j + 1));
            p3=2*(slices +1)*(i+1) +j*2;
            p4=2*(slices +1)*(i+1) +(2*(j + 1));
            p5 = p1 + 1;
            p6 = p2 + 1;
            p7 = p3 + 1;
            p8 = p4 + 1;
        
            //Triangulo 1 Cima
            outfile << p1 << " " << p2 << " " << p3 << " ";
            //Triangulo 2 Cima
            outfile << p4 << " " << p3 << " " << p2 << " ";

            //Triangulo 1 Baixo
            outfile << p5 << " " << p7 << " " << p8 << " ";
            //Triangulo 2 Baixo
            outfile << p8 << " " << p6 << " " << p5 << " ";

        }
    }
    outfile.flush();
    outfile.close();

}


void cone(float radius, float height, float slices, float stacks,char * file){
    std::ofstream outfile;
    outfile.open(file);
    //BASE
	for (int k = 0;k < slices;k++) {

        outfile << radius * sin((k+1) * ((2 * M_PI) / slices)) << " " << 0 << " " << radius * cos((k+1) * ((2 * M_PI) / slices)) << " ";
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << 1.0f/ (radius * sin((k+1) * ((2 * M_PI) / slices))) << " " << 1.0f/(radius * cos((k+1) * ((2 * M_PI) / slices))) << " ";

        outfile << radius*sin(k*((2*M_PI)/slices)) << " " << 0 << " " << radius*cos(k * ((2 * M_PI) / slices)) << " ";
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << 1.0f/(radius*sin(k*((2*M_PI)/slices))) << " " << 1.0f/(radius*cos(k * ((2 * M_PI) / slices))) << " ";

        outfile << 0 << " " << 0 << " " << 0 << " ";	
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << 0.0f << " " << 0.0f<< " ";


	}
	//RESTO
	float y=0, next_y, next_r, r =radius;
	float betac = (atan(radius/height));
	for (int i = 0; i <stacks; i++) {
		next_y = y + height / stacks;
		next_r = r - (radius/ stacks);
		for (int j = 0;j < slices;j++) {
            outfile << r * sin(j * ((2 * M_PI) / slices)) << " " << y << " " << r * cos(j * ((2 * M_PI) / slices)) << " ";
            outfile << sin(j * ((2 * M_PI) / slices))* cos(betac) << " " << sin(betac) << " " << cos(betac) * cos(j * ((2 * M_PI) / slices)) << " ";

            outfile << r * sin((j + 1) * ((2 * M_PI) / slices)) << " " << y << " " << r * cos((j + 1) * ((2 * M_PI) / slices)) << " ";
            outfile << cos(betac) * sin((j+1) * ((2 * M_PI) / slices)) << " " << sin(betac) << " " << cos(betac) * cos((j+1) * ((2 * M_PI) / slices)) << " ";

            outfile << next_r * sin(j * ((2 * M_PI) / slices)) << " " << next_y << " " << next_r * cos(j * ((2 * M_PI) / slices)) << " ";
            outfile << cos(betac) * sin(j * ((2 * M_PI) / slices)) << " " << sin(betac) << " " << cos(betac) * cos(j * ((2 * M_PI) / slices)) << " ";


            outfile << next_r * sin(j * ((2 * M_PI) / slices)) << " " << next_y << " " << next_r * cos(j * ((2 * M_PI) / slices)) << " ";
            outfile << cos(betac) * sin(j * ((2 * M_PI) / slices)) << " " << sin(betac) << " " << cos(betac) * cos(j * ((2 * M_PI) / slices)) << " ";

            outfile << r * sin((j + 1) * ((2 * M_PI) / slices)) << " " << y << " " << r * cos((j + 1) * ((2 * M_PI) / slices)) << " ";
            outfile << cos(betac) * sin((j+1) * ((2 * M_PI) / slices)) << " " << sin(betac) << " " << cos(betac) * cos((j+1) * ((2 * M_PI) / slices)) << " ";

            outfile << next_r * sin((j + 1) * ((2 * M_PI) / slices)) << " " << next_y << " " <<  next_r * cos((j + 1) * ((2 * M_PI) / slices)) << " ";
            outfile << cos(betac) * sin((j+1) * ((2 * M_PI) / slices)) << " " << sin(betac) << " " << cos(betac) * cos((j+1) * ((2 * M_PI) / slices)) << " ";
			

		}
		r = next_r;
		y = next_y;
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

	for (int i = 0; i < sides; ++i) {
		// top
		// central point
        outfile << 0.0f << " " << height /2.0f << " " << 0.0f << " ";
        outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
        outfile << 0.4375f << " " << 0.1875f << " ";

        outfile << radius * sin( i * delta) << " " << height /2.0f << " " << radius * cos( i * delta) << " ";
        outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
        outfile << 0.4375 + (0.1875 * sin(i * delta)) << " " << 0.1875 + (0.1875 * cos(i * delta)) << " ";


        outfile << radius * sin( (i+1) * delta) << " " << height /2.0f << " " << radius * cos( (i+1) * delta) << " ";
        outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
        outfile << 0.4375 + (0.1875 * sin((i+1) * delta)) << " " <<  0.1875 + (0.1875 * cos((i+1) * delta)) << " ";


		// body
		// tri�ngulo 1
        outfile << radius * sin( (i+1) * delta) << " " << height /2.0f << " " << radius * cos( (i+1) * delta) << " ";
        outfile << sin((i + 1) * delta) << " " << 0.0f << " " << cos((i + 1) * delta) << " ";
        outfile << (i+1)/(float)sides<< " " << 1<< " ";
       
        outfile << radius * sin( i * delta) << " " << height /2.0f << " " << radius * cos( i * delta) << " ";
        outfile << sin(i*delta) << " " << 0.0f << " " << cos(i*delta) << " ";
        outfile << (i)/(float)sides<< " " << 1<< " ";

        outfile << radius * sin( i * delta) << " " << -height /2.0f << " " << radius * cos( i * delta) << " ";
        outfile << sin(i*delta) << " " << 0.0f << " " << cos(i*delta) << " ";
        outfile << (i+1)/(float)sides<< " " << 0.375f << " ";


		// triangle 2
        outfile << radius * sin ((i+1) * delta) << " " << -height/2.0f << " " << radius * cos( (i+1) * delta) << " ";
        outfile << sin ((i+1) * delta) << " " << 0.0f << " " << cos( (i+1) * delta) << " ";
        outfile << (i+1)/(float)sides<< " " << 0.375f << " ";


        outfile << radius * sin( (i+1) * delta) << " " << height /2.0f << " " << radius * cos( (i+1) * delta) << " ";
        outfile << sin ((i+1) * delta) << " " << 0.0f << " " << cos( (i+1) * delta) << " ";
        outfile << (i+1)/(float)sides<< " " << 1.0f << " ";


        outfile << radius * sin( i * delta) << " " << -height/2.0f << " " << radius * cos( i * delta) << " ";
        outfile << sin (i * delta) << " " << 0.0f << " " << cos( i * delta) << " ";
        outfile << (i)/(float)sides<< " " << 0.375f << " ";

		// base
		// central point
        outfile << 0.0f << " " << -height / 2.0f << " " << 0.0f << " ";
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << 0.8125 << " " << 0.1875 << " ";


        outfile << radius*sin((i+1)*delta) << " " << -height / 2.0f << " " << radius * cos( (i+1) * delta) << " ";
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << 0.8125 + (0.1875 * sin(i * delta)) << " " << 0.1875 + (0.1875 * cos(i * delta)) << " ";
        
        outfile << radius * sin( i * delta) << " " << -height / 2.0f << " " << radius * cos( i * delta) << " ";
        outfile << 0.0f << " " << -1.0f << " " << 0.0f << " ";
        outfile << 0.8125 + (0.1875 * sin((i+1) * delta)) << " " << 0.1875 + (0.1875 * cos((i+1) * delta)) << " ";

	}
    outfile.flush();
    outfile.close();
}


void flatRing( float inner, float outer, int sides,int stacks, char * file){
    std::ofstream outfile;
    outfile.open(file);
    for(int i=0; i<stacks; i++){
        for(int j=0; j<sides;j++){
            float r = inner + i*(outer-inner)/(float)stacks;
            float next_r = inner + (i+1)*(outer-inner)/(float)stacks;
            float x = cos(j*2.0f * M_PI / (float)sides);
            float z = sin(j*2.0f * M_PI / (float)sides);
            float next_x = cos((j+1)*2.0f * M_PI / (float)sides);
            float next_z = sin((j+1)*2.0f * M_PI / (float)sides);

            outfile << r*x << " " << 0.0f << " " << r*z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";

            outfile << r*next_x << " " << 0.0f << " " << r*next_z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";

            outfile << next_r*x << " " << 0.0f << " " << next_r*z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";

            outfile << r*next_x << " " << 0.0f << " " << r*next_z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";

            outfile << next_r*next_x << " " << 0.0f << " " << next_r*next_z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";

            outfile << next_r*x << " " << 0.0f << " " << next_r*z << " ";
            outfile << 0.0f << " " << 1.0f << " " << 0.0f << " ";
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
        for(int u=0;u<level;u++)
            for(int v=0;v<level;v++){
                float pos[3],du[3],dv[3],normal[3];
                getBezierPoint(u/(float)level,v/(float)level,patch_points,pos,du,dv);
                cross(dv,du,normal);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                outfile << normal[0] << " " << normal[1] << " " << normal[2] << " ";

                getBezierPoint(u/(float)level,(v+1)/(float)level,patch_points,pos,du,dv);
                cross(dv,du,normal);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                outfile << normal[0] << " " << normal[1] << " " << normal[2] << " ";

                getBezierPoint((u+1)/(float)level,v/(float)level,patch_points,pos,du,dv);
                cross(dv,du,normal);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                outfile << normal[0] << " " << normal[1] << " " << normal[2] << " ";

                getBezierPoint((u+1)/(float)level,(v+1)/(float)level,patch_points,pos,du,dv);
                cross(dv,du,normal);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                outfile << normal[0] << " " << normal[1] << " " << normal[2] << " ";

                getBezierPoint((u+1)/(float)level,v/(float)level,patch_points,pos,du,dv);
                cross(dv,du,normal);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                outfile << normal[0] << " " << normal[1] << " " << normal[2] << " ";

                getBezierPoint(u/(float)level,(v+1)/(float)level,patch_points,pos,du,dv);
                cross(dv,du,normal);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                outfile << normal[0] << " " << normal[1] << " " << normal[2] << " ";
                
            }
    }
    
    outfile.flush();
    outfile.close();
    

    
}


int main(int argc, char** argv) {
    std::string shape = argv[1];

	if (shape == "plane")  plane(std::stoi(argv[2]),std::stoi( argv[3]),argv[4]);
	else if (shape == "box") box(std::stoi(argv[2]),std::stoi( argv[3]),argv[4]);
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