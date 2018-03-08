#include <stdio.h>
#include <stdlib.h>


typedef float Point3[3];
typedef int Face[3];

typedef struct{
    int nvert, nfaces, nedges;
    Point3 *verticies;
    Face *faces;
} Object3D;

void readOFFFile(const char *fname, Object3D *shape ){
    char str[10];  //string at start of file, discarded.
    int i, n;
    FILE * fp;

    fp = fopen (fname,"r"); //open file for reading
    fscanf (fp, "%s %d %d %d", str, &shape->nvert, &shape->nfaces, &shape->nedges);  //scan index values into struct
    shape->verticies = (Point3*)malloc(shape->nvert * sizeof(Point3));  //initialise array of vectors

    for (i=0; i<shape->nvert; i++){  //increment through point list in OFF file.
        fscanf(fp,"%f %f %f", &shape->verticies[i][0], &shape->verticies[i][1], &shape->verticies[i][2]); //scan in vectors into array
    }

    shape->faces = (Face*)malloc(shape->nfaces * sizeof(Face)); //initialise array of nfaces

    for(i=0; i<shape->nfaces; i++){   //increment through nfaces list in off file
        fscanf(fp,"%d %d %d %d", &n, &shape->faces[i][0], &shape->faces[i][1], &shape->faces[i][2]);   //scan number of verticies in this face
        }

    fclose(fp); //close file

}

void writeOFFFile (char fname[25], const Object3D *shape){
    FILE * fp;
    int i;

    fp = fopen (fname,"w"); //open file for writing
    fprintf(fp, "OFF\n");
    fprintf(fp, "%d %d %d\n", shape->nvert, shape->nfaces, shape->nedges); //write counts
    for (i = 0; i<shape->nvert; i++){
        fprintf(fp, "%f %f %f \n", shape->verticies[i][0], shape->verticies[i][1], shape->verticies[i][2]);  //write points
    }
    for (i = 0; i< shape->nvert; i++){
     fprintf(fp, "%d %d %d %d\n", 3 , shape->faces[i][0], shape->faces[i][1], shape->faces[i][2]);  //write faces
    }
    fclose(fp);
}


int main(){

    int i;
    char fname[25] = "bone.off";
    char wname[25] = "new.off";

    Object3D shape;
    readOFFFile(fname, &shape);
    writeOFFFile(wname, &shape);

}

