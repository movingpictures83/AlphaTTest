#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "AlphaTTestPlugin.h"

void AlphaTTestPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }
 
}

void AlphaTTestPlugin::run() {
   
}

void AlphaTTestPlugin::output(std::string file) {
//beta_diversity.py -i filtered_otu_table.biom -m euclidean,weighted_unifrac,unweighted_unifrac -t rep_set.tre -o beta_div
   std::string command = "compare_alpha_diversity.py ";
 command += "-i "+std::string(PluginManager::prefix())+"/"+parameters["matrix"];
 command += " -m "+std::string(PluginManager::prefix())+"/"+parameters["mapping"];
 //command += " -p none";
 command += " -d "+parameters["depth"];
 command += " -t "+parameters["test"];
 command += " -c "+parameters["column"];
 command += " -o "+file+"; cp "+file+"/Description_stats.txt "+file+"/..";//; export PYTHONPATH=OLDPATH";
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<AlphaTTestPlugin> AlphaTTestPluginProxy = PluginProxy<AlphaTTestPlugin>("AlphaTTest", PluginManager::getInstance());
