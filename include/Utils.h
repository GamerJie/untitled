//
// Created by Jie on 2018/8/4.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H


#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <io.h>

#ifdef linux
#include <unistd.h>
#endif

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;


class Utils {
public:
    //static void GetFiles(string path, vector<string> &files) {
    //    //文件句柄
    //    long hFile = 0;
    //    //文件信息
    //    struct _finddata_t fileinfo;
    //    string p;
    //    if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1) {
    //        do {
    //            if ((fileinfo.attrib & _A_SUBDIR)) {
    //                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
    //                    GetFiles(p.assign(path).append("/").append(fileinfo.name), files);
    //            } else {
    //                files.push_back(p.assign(path).append("/").append(fileinfo.name));
    //            }
    //        } while (_findnext(hFile, &fileinfo) == 0);
    //        _findclose(hFile);
    //    }
    //}


    static bool TraverseFiles(string path,int &file_num) {
        _finddata_t file_info{};
        string current_path = path + "/*.*";

        int handle = _findfirst(current_path.c_str(), &file_info);

        if (-1 == handle)
            return false;

        do {
            string attribute;
            if (file_info.attrib == _A_SUBDIR)
                attribute = "dir";
            else
                attribute = "file";

            cout << file_info.name << ' ' << file_info.time_write << ' ' << file_info.size << ' ' << attribute
                 << endl;
            file_num++;

        } while (!_findnext(handle, &file_info));

        _findclose(handle);
        return true;
    }

    static void DfsFolder(string path, vector<string> &files, string filter = "*", int layer = 0) {
        _finddata_t file_info{};
        string current_path = path + "/*." + filter;
        int handle = _findfirst(current_path.c_str(), &file_info);

        if (-1 == handle) {
            cout << "cannot match the path" << endl;
            return;
        }

        do {

            if (file_info.attrib == _A_SUBDIR) {

                for (int i = 0; i < layer; i++)
                    cout << "--";
                files.push_back(file_info.name);

                int layer_tmp = layer;
                if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
                    DfsFolder(path + '/' + file_info.name, files, filter, layer_tmp + 1);
            } else {

                for (int i = 0; i < layer; i++)
                    cout << "--";
                files.push_back(file_info.name);
            }
        } while (!_findnext(handle, &file_info));

        _findclose(handle);
    }


    static void Relpace(std::string &strBig, const std::string &strsrc, const std::string &strdst) {
        std::string::size_type pos = 0;
        std::string::size_type srclen = strsrc.size();
        std::string::size_type dstlen = strdst.size();

        while ((pos = strBig.find(strsrc, pos)) != std::string::npos) {
            strBig.replace(pos, srclen, strdst);
            pos += dstlen;
        }
    }

    static void UPDir(std::string &dir) {
        Relpace(dir, "\\", "/");
        auto res = dir.rfind('/');
        if (res != string::npos) {
            dir.erase(res, dir.length() - res);
        }
    }


    static bool DirExists(const std::string &dirName_in) {
        int ftyp = _access(dirName_in.c_str(), 0);

        if (0 == ftyp)
            return true;   // this is a directory!
        else
            return false;    // this is not a directory!
    }

	static std::string Formart(json j) {
		return Formart(j.dump());
	}

	static std::string StrLine(unsigned int line) {
		std::string fm("\n");
		for (unsigned int j = 0; j < line; j++)
			fm += '\t';

		return fm;
	}

	static std::string Formart(std::string s) {
		unsigned int depth = 0;
		for (unsigned int i = 0; i < s.size(); i++) {
			if (s[i] == '{' || s[i] == '[') {
				depth++;
				auto str = StrLine(depth);
				s.insert(i + 1, str);
				i += str.size();
			}
			else if (s[i] == ',') {
				auto str = StrLine(depth);
				s.insert(i + 1, str);
				i += str.size();
			}
			else if (s[i] == '}' || s[i] == ']') {
				depth--;
				auto str = StrLine(depth);
				s.insert(i, str);
				i += str.size();
			}
		}

		return "json ===> \n" + s;
	}
};

#endif //UNTITLED_UTILS_H
