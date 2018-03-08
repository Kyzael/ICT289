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
    char str[10];  //string at start of file, discarded.
    int i, n;

    FILE * fp;
    fp = fopen (fname,"r"); //open file for reading
    fscanf (fp, "%s %d %d %d", str, &shape->nvert, &shape->nfaces, &shape->nedges);  //scan index values into struct
    shape->list_verticies = malloc(shape->nvert * sizeof(Point3));  //initialise array of vectors

    for (i=0; i<shape->nvert; i++){  //increment through point list in OFF file.
        fscanf(fp,"%f %f %f", &shape->list_verticies[i].x, &shape->list_verticies[i].y, &shape->list_verticies[i].z); //scan in vectors into array
    }

    shape->list_faces = (Face*)malloc(shape->nfaces * sizeof(Face)); //initialise array of nfaces

    for(i=0; i<shape->nfaces; i++){   //increment through nfaces list in off file
        fscanf(fp, "%d ", &shape->list_faces[i].nvert);
        shape->list_faces[i].index = malloc(shape->list_faces[i].nvert * sizeof(int));
        
        for(n=0; n<shape->list_faces[i].nvert; n++){
             fscanf(fp,"%d ", &shape->list_faces[i].index[n]);
        }
    }

    fclose(fp); //close file

}

void writeOFFFile (char fname[25], const Object3D *shape){
    FILE * fp;
    int i, n;

    fp = fopen (fname,"w"); //open file for writing
    fprintf(fp, "OFF\n");
    fprintf(fp, "%d %d %d\n", shape->nvert, shape->nfaces, shape->nedges); //write counts
    for (i = 0; i<shape->nvert; i++){
        fprintf(fp, "%f %f %f \n", shape->list_verticies[i].x, shape->list_verticies[i].y, shape->list_verticies[i].z);  //write points
    }
    for (i = 0; i< shape->nfaces; i++){
        fprintf(fp, "%d ", shape->list_faces[i].nvert );
    
        for(n=0; n< shape->list_faces[i].nvert; n++){
            fprintf(fp, "%d ", shape->list_faces[i].index[n]);  //write list_faces
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
