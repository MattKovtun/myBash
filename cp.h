//
// Created by matt on 3/20/17.
//

#ifndef MYBASH_CP_H
#define MYBASH_CP_H

#endif //MYBASH_CP_H


bool cp() {
    fs::path destination_path("/home/matt/CLionProjects/myBash/copy_test.txt");
    fs::path source_path("/home/matt/CLionProjects/myBash/copy_test_res.txt");
    fs::copy_file(source_path, destination_path, fs::copy_option::overwrite_if_exists);
    //fs::copy_option::overwrite_if_exists

}
