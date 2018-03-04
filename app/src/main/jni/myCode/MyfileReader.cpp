//
// Created by javan on 3/3/2018.
//

#include "MyfileReader.h"
#include "../common/misc.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

MyfileReader::MyfileReader() {

    /* for (int i = 0; i < 256; i++) {
         vertex[i].x = 0;
         vertex[i].y = 0;
         vertex[i].z = 0;
     }*/
}

MyfileReader::~MyfileReader() {

}

void
MyfileReader::load_obj(std::string assetName, std::string &filename, MyMesh *mesh) {
    // construct the filename in internal storage by concatenating with path to internal storage
    filename = GetFileName(assetName);
    std::string filenamePath = apkInternalPath + "/" + filename;
    // check if the file was previously extracted and is available in app's internal dir
    FILE *file1 = fopen(filenamePath.c_str(), "rb");
    if (file1) {
        MyLOGI("Found extracted file in assets: %s", filenamePath.c_str());
        fclose(file1);
    }

    std::ifstream in(filename, std::ios::in);
    if (!in) {
        MyLOGE("Can't open %s", filenamePath.c_str());
        MyLOGE("Can't open %s", filenamePath.c_str());
        exit(0);
    }
    std::string line;
    while (getline(in, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            glm::vec4 v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            v.w = 1.0f;
            mesh->vertices.push_back(v);
        } else if (line.substr(0, 2) == "f ") {
            std::istringstream s(line.substr(2));
            GLushort a, b, c;
            s >> a;
            s >> b;
            s >> c;
            a--;
            b--;
            c--;
            mesh->elements.push_back(a);
            mesh->elements.push_back(b);
            mesh->elements.push_back(c);
        } else if (line[0] == '#') {
            /* ignoring this line */
        } else {
            /* ignoring this line */
        }
    }

    mesh->normals.resize(mesh->vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < mesh->elements.size(); i += 3) {
        GLushort ia = mesh->elements[i];
        GLushort ib = mesh->elements[i + 1];
        GLushort ic = mesh->elements[i + 2];
        glm::vec3 normal = glm::normalize(glm::cross(
                glm::vec3(mesh->vertices[ib]) - glm::vec3(mesh->vertices[ia]),
                glm::vec3(mesh->vertices[ic]) - glm::vec3(mesh->vertices[ia])));
        mesh->normals[ia] = mesh->normals[ib] = mesh->normals[ic] = normal;
    }

}

/**
 * Search for a file in assets, extract it, save it in internal storage, and return the new path
 */
void MyfileReader::loade(std::string assetName, std::string &filename) {
    // construct the filename in internal storage by concatenating with path to internal storage
    filename = apkInternalPath + "/" + GetFileName(assetName);

    // check if the file was previously extracted and is available in app's internal dir
    FILE *file1 = fopen(filename.c_str(), "rb");
    if (file1) {
        MyLOGI("Found extracted file in assets: %s", filename.c_str());
        fclose(file1);
    }
    std::ifstream file;
    file.open(filename);

    std::string str;

    while (!file.eof()) //while we are still in the file
    {
        getline(file, str); //move one line down
        if (str[0] == 'v') break; //if we have a vertex line, stop
    }

    int v = 0;

    while (str[0] == 'v') {

        int i = 0;

        while (true) {
            while (str[i] == ' ') {
                i++; //move a space over
            }
            i++;
            i++;
            int j = i, k = i;
            while (str[i] != ' ') {
                i++;
                k = i;
            }
            vertex[v].x = (float) atof(str.substr(j, k - j).c_str());

            //moving on to the y coord

            while (str[i] == ' ') {
                i++;
            }

            int q = i, w = i;
            while (str[i] != ' ') {
                i++;
                w = i;
            }
            vertex[v].y = (float) atof(str.substr(q, w - q).c_str());

            while (str[i] == ' ') {
                i++;
            }

            int a = i, s = i;
            while (str[i] != ' ') {
                i++;
                s = i;
            }
            vertex[v].z = (float) atof(str.substr(a, s - a).c_str());

            break;
        }
        v++;
        getline(file, str);
    }
    /*  // let us look for the file in assets
      bool result = false;

      // Open file
      AAsset* asset = AAssetManager_open(apkAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);

      char buf[BUFSIZ];
      int nb_read = 0;
      if (asset != NULL)
      {

          FILE* out = fopen(filename.c_str(), "w");
          while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
          {
              fwrite(buf, nb_read, 1, out);
          }
          fclose(out);
          AAsset_close(asset);
          result = true;

          MyLOGI("Asset extracted: %s", filename.c_str());
      }
      else {
          MyLOGE("Asset not found: %s", assetName.c_str());
      }

      return result;*/
}
