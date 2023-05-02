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
	for (int i = 0; i < divs; i++) {
		z=size/2;
		for (int j = 0; j < divs; j++){
            outfile << x << " " << 0.0f << " " << z << " ";
            outfile << x+size/divs << " " << 0.0f << " " << z << " ";
            outfile << x << " " << 0.0f << " " << z-size/divs << " ";

            outfile << x+size/divs << " " << 0.0f << " " << z-size/divs << " ";
            outfile << x << " " << 0.0f << " " << z-size/divs << " ";
            outfile << x + size / divs << " " << 0.0f << " " << z << " ";
			z -= size / divs;
		}
		x += size / divs;
	}
    outfile.flush();
    outfile.close();
}

void box(float len, float divs,char * file){
    std::ofstream outfile;
    outfile.open(file);
    float x = -len / 2,z;

	for (int i = 0; i < divs; i++) {
		z = len / 2;
		for (int j = 0; j < divs; j++) {

			//TOPG
            outfile << x << " " << len/2 << " " << z << " ";
            outfile << x + len / divs << " " << len/2 << " " << z << " ";
            outfile << x << " " << len/2 << " " << z - len / divs << " ";

            outfile << x + len / divs << " " << len/2 << " " << z - len / divs << " ";
            outfile << x << " " << len/2 << " " << z - len / divs << " ";
            outfile << x + len / divs << " " << len/2 << " " << z << " ";
			

			//face1

            outfile << len/2 << " " << x << " " << z - len / divs << " ";
            outfile << len/2 << " " << x + len / divs << " " << z << " ";
            outfile << len/2 << " " << x << " " << z << " ";


            outfile << len/2 << " " << x + len / divs << " " << z << " ";
            outfile << len/2 << " " << x << " " << z - len / divs << " ";
            outfile << len/2 << " " << x + len / divs << " " << z - len / divs << " ";
			
			

			//face2

            outfile << -len/2 << " " << x << " " << z << " ";
            outfile << -len/2 << " " << x + len / divs << " " << z << " ";
            outfile << -len/2 << " " << x << " " << z - len / divs << " ";

            outfile << -len/2 << " " << x + len / divs << " " << z - len / divs << " ";
            outfile << -len/2 << " " << x << " " << z - len / divs << " ";
            outfile << -len/2 << " " << x + len / divs << " " << z << " ";
			
		
			//face3

            outfile <<  x + len / divs << " " << z << " " << len / 2 << " ";
            outfile << x << " " << z - len / divs << " " << len / 2 << " ";
            outfile <<  x + len / divs << " " << z - len / divs << " " << len / 2 << " ";


            outfile <<  x << " " << z - len / divs << " " << len / 2 << " ";
            outfile << x + len / divs << " " << z << " " << len / 2 << " ";
            outfile <<  x << " " << z << " " << len / 2 << " ";
			
			
			

			//face4

            outfile <<  x + len / divs << " " << z - len / divs << " " << -len / 2 << " ";
            outfile << x << " " << z - len / divs << " " << -len / 2 << " ";
            outfile <<  x + len / divs << " " << z << " " << -len / 2 << " ";

            outfile <<  x << " " << z << " " << -len / 2 << " ";
            outfile << x + len / divs << " " << z << " " << -len / 2 << " ";
            outfile <<  x + len / divs << " " << z - len / divs << " " << -len / 2 << " ";
			
			
			
			//BASED

            outfile << x + len / divs << " " << - len / 2 << " " << z << " ";
            outfile << x << " " << - len / 2 << " " << z - len / divs << " ";
            outfile << x + len / divs << " " << - len / 2 << " " << z - len / divs << " ";


            outfile << x << " " << - len / 2 << " " << z - len / divs << " ";
            outfile << x + len / divs << " " << - len / 2 << " " << z << " ";
            outfile << x << " " << - len / 2 << " " << z << " ";
			
			z -= len / divs;
		}
		x += len / divs;
	}
    outfile.flush();
    outfile.close();
    
}


void sphere(float radius, float slices, float stacks,char * file) {
    std::ofstream outfile;
    outfile.open(file);
	float next_a, next_b, a = 0, b = 0, y, next_y;
	for (int i = 0; i < stacks / 2;i++) {
		a = 0;
		next_b = b + (M_PI / stacks);
		y = radius * sin(b);
		next_y = radius * sin(next_b);
		for (int j = 0; j < slices; j++) {
			next_a = a + ((2 * M_PI) / slices);

            outfile << radius *cos(b)*sin(a) << " " << y << " " << radius*cos(b)*cos(a) << " ";
            outfile << radius * cos(b) * sin(next_a) << " " << y << " " << radius * cos(b) * cos(next_a) << " ";
            outfile << radius * cos(next_b) * sin(a) << " " << next_y << " " << radius * cos(next_b) * cos(a) << " ";

            outfile << radius * cos(next_b) * sin(next_a) << " " << next_y << " " << radius * cos(next_b) * cos(next_a) << " ";
            outfile << radius * cos(next_b) * sin(a) << " " << next_y << " " << radius * cos(next_b) * cos(a) << " ";
            outfile << radius * cos(b) * sin(next_a) << " " << y << " " << radius * cos(b) * cos(next_a) << " ";



            
            outfile << radius * cos(b) * sin(a) << " " <<  -y << " " << radius * cos(b) * cos(a) << " ";
            outfile << radius * cos(next_b) * sin(a)  << " " << - next_y << " " << radius * cos(next_b) * cos(a) << " ";
            outfile << radius * cos(next_b) * sin(next_a) << " " << - next_y << " " << radius * cos(next_b) * cos(next_a) << " ";



            outfile << radius * cos(next_b) * sin(next_a) << " " <<  -next_y << " " << radius * cos(next_b) * cos(next_a) << " ";
            outfile << radius * cos(b) * sin(next_a) << " " << - y << " " << radius * cos(b) * cos(next_a) << " ";
            outfile << radius * cos(b) * sin(a) << " " << - y << " " <<  radius * cos(b) * cos(a) << " ";

			
			a = next_a;
		}
		y = next_y;
		b = next_b;
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
        outfile << radius*sin(k*((2*M_PI)/slices)) << " " << 0 << " " << radius*cos(k * ((2 * M_PI) / slices)) << " ";
        outfile << 0 << " " << 0 << " " << 0 << " ";	

	}
	//RESTO
	float y=0, next_y, next_r, r =radius;
	for (int i = 0; i <stacks; i++) {
		next_y = y + height / stacks;
		next_r = r - (radius/ stacks);
		for (int j = 0;j < slices;j++) {

            outfile << r * sin(j * ((2 * M_PI) / slices)) << " " << y << " " << r * cos(j * ((2 * M_PI) / slices)) << " ";
            outfile << r * sin((j + 1) * ((2 * M_PI) / slices)) << " " << y << " " << r * cos((j + 1) * ((2 * M_PI) / slices)) << " ";
            outfile << next_r * sin(j * ((2 * M_PI) / slices)) << " " << next_y << " " << next_r * cos(j * ((2 * M_PI) / slices)) << " ";
			

            outfile << next_r * sin(j * ((2 * M_PI) / slices)) << " " << next_y << " " << next_r * cos(j * ((2 * M_PI) / slices)) << " ";
            outfile << r * sin((j + 1) * ((2 * M_PI) / slices)) << " " << y << " " << r * cos((j + 1) * ((2 * M_PI) / slices)) << " ";
            outfile << next_r * sin((j + 1) * ((2 * M_PI) / slices)) << " " << next_y << " " <<  next_r * cos((j + 1) * ((2 * M_PI) / slices)) << " ";

			

		}
		r = next_r;
		y = next_y;
	}
    outfile.flush();
    outfile.close();
    
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



void getBezierPoint(float u, float v, float **points, float *pos) {
    float m[4][4] = {{-1, 3, -3, 1},
                   {3, -6, 3, 0},
                   {-3, 3, 0, 0},
                   {1, 0, 0, 0}};

    float U[4] = {u * u * u, u * u, u, 1};
    float V[4] = {v * v * v, v * v, v, 1};
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
	for (int i = 0; i < 3; i++) {
		multVectorMatrix(U,m[0], A);
        multVectorMatrix(A,Ps[i],B);
        multVectorMatrix(B,m[0],A);
        pos[i] = multVectorVector(A,V);
	}
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
                float pos[3];
                getBezierPoint(u/(float)level,v/(float)level,patch_points,pos);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                getBezierPoint(u/(float)level,(v+1)/(float)level,patch_points,pos);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                getBezierPoint((u+1)/(float)level,v/(float)level,patch_points,pos);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";

                getBezierPoint((u+1)/(float)level,(v+1)/(float)level,patch_points,pos);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                getBezierPoint((u+1)/(float)level,v/(float)level,patch_points,pos);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
                getBezierPoint(u/(float)level,(v+1)/(float)level,patch_points,pos);
                outfile << pos[0] << " " << pos[1] << " " << pos[2] << " ";
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
    else if (shape=="patch") patch(argv[2],std::stoi(argv[3]),argv[4]);//generator patch teapot.patch 10 bezier_10.3d
	else {
		std::cout << "Erro: Figura não suportada";
		return 1;
	}
    return 0;
}