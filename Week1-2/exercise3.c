#include <stdio.h>
#include <stdlib.h>

typedef struct Point3{
    float x, y, z; 
 } Point3;

typedef  struct Face{
    int nvert;
    int *index;  
} Face;

typedef struct Object3D{  
    int nvert, nfaces, nedges;
    Point3 *list_verticies;
    Face *list_faces;
} Object3D;

void readOFFFile(const char *fname, Object3D *shape ){
    char str[10];
    int i, n;

    FILE * fp;
    fp = fopen (fname,"r"); 
    fscanf (fp, "%s %d %d %d", str, &shape->nvert, &shape->nfaces, &shape->nedges);  //Read number of verticies and faces in the OFF file. Change this to read all strings before the first int.
    shape->list_verticies = malloc(shape->nvert * sizeof(Point3));  //initialise the array of verticies. (nvert * Point3)

    for (i=0; i<shape->nvert; i++){  //increment through list of verticies in the file.
        fscanf(fp,"%f %f %f", &shape->list_verticies[i].x, &shape->list_verticies[i].y, &shape->list_verticies[i].z); //read points into array of structs.
    }

    shape->list_faces = (Face*)malloc(shape->nfaces * sizeof(Face)); //initialise array of face. (nfaces * Face)
    
    for(i=0; i<shape->nfaces; i++){   //increment through list of faces in the file.
        fscanf(fp, "%d ", &shape->list_faces[i].nvert);  // Red in the number indexes the face is commprised of
        shape->list_faces[i].index = malloc(shape->list_faces[i].nvert * sizeof(int)); //set isze of the array containing face indexes.
        
        for(n=0; n<shape->list_faces[i].nvert; n++){ 
             fscanf(fp,"%d ", &shape->list_faces[i].index[n]); //read each index into array
        }
    }

    fclose(fp); //close file
}

void writeOFFFile (char fname[25], const Object3D *shape){
    FILE * fp;
    int i, n;

    fp = fopen (fname,"w"); //open file for writing
    fprintf(fp, "OFF\n");
    fprintf(fp, "%d %d %d\n", shape->nvert, shape->nfaces, shape->nedges); //write tallies
    for (i = 0; i<shape->nvert; i++){
        fprintf(fp, "%f %f %f \n", shape->list_verticies[i].x, shape->list_verticies[i].y, shape->list_verticies[i].z);  //write verticies list
    }
    for (i = 0; i< shape->nfaces; i++){
        fprintf(fp, "%d ", shape->list_faces[i].nvert );
    
        for(n=0; n< shape->list_faces[i].nvert; n++){
            fprintf(fp, "%d ", shape->list_faces[i].index[n]);  //write face list
        }
        fprintf(fp, "\n");
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
