#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

enum class color {
    black, red, green, yellow, blue, purple, cyan, white, default_color
};

struct cfg {
   std::map<char, color> cfg_data;

   void load_cfg(const std::string& cfg_path);
   void show_cfg();
};

void cfg::load_cfg(const std::string& cfg_path)
{
   std::ifstream cfgFIle(cfg_path);
   std::string line;
   while(std::getline(cfgFIle, line)) {
      size_t word_cnt = 0;
      std::istringstream ss{line};
      std::string word;
      char prev_letter {};
      while(ss >> word) {
         if(word_cnt >= 2) {
            std::cout << "error cfg format" << std::endl;
            throw std::logic_error("error cfg format");
         }

         if(prev_letter == char()) {
            if(word.size() > 1) {
               std::cout << "error cfg line" << std::endl;
               throw std::logic_error("error cfg line");
            }
            prev_letter = word[0];
         }
         else {
            enum class letter_colors {
               black = 'd', red = 'r', green = 'g', yellow = 'y', blue = 'b', purple = 'p', 
                  cyan = 'c', white = 'w', default_color = 'd'
            };

            switch(word[0])
            {
               case char(letter_colors::black):
                  cfg_data[prev_letter] = color::black;
                  break;
               case char(letter_colors::red):
                  cfg_data[prev_letter] = color::red;
                  break;
               case char(letter_colors::green):
                  cfg_data[prev_letter] = color::green;
                  break;
               case char(letter_colors::yellow):
                  cfg_data[prev_letter] = color::yellow;
                  break;
               case char(letter_colors::blue):
                  cfg_data[prev_letter] = color::blue;
                  break;
               case char(letter_colors::purple):
                  cfg_data[prev_letter] = color::purple;
                  break;
               case char(letter_colors::cyan):
                  cfg_data[prev_letter] = color::cyan;
                  break;
               case char(letter_colors::white):
                  cfg_data[prev_letter]  = color::white;
                  break;
               default:
                  cfg_data[prev_letter] = color::default_color;
                  break;
            }
         }

         word_cnt++;
      }
   }
}

#if 1
void cfg::show_cfg()
{
   for(const auto&[letter, ncolor] : cfg_data) {
      std::cout << letter << " / color id = " << int(ncolor) << std::endl;
   }
}
#endif

class linuxcolor_t {
private:
   std::ostream& os_;
   std::map<color, const char*> colors;
   cfg color_cfg;
public:
   linuxcolor_t(std::ostream& os, cfg& cfg_) : os_(os), color_cfg(cfg_)
   {
      colors[color::black] = "\033[0;30m";
      colors[color::red] = "\033[0;31m";
      colors[color::green] = "\033[0;31m";
      colors[color::yellow] = "\033[0;33m";
      colors[color::blue] = "\033[0;34m";
      colors[color::purple] = "\033[0;35m";
      colors[color::cyan] = "\033[0;36m";
      colors[color::white] = "\033[0;37m"; 
      colors[color::default_color] = "\033[0m";
   }

   template<typename T>
   void color_print(T output, color color) {
    os_ << colors[color] << output << colors[color]; 
   }

   void image_print(const char* image_path) {
    std::ifstream imageFIle(image_path);
    std::string line;
    while(std::getline(imageFIle, line)) {
        for(size_t i = 0; i < line.size(); i++) {

            if(i == line.size() - 1) {
                color_print("\n", color::default_color);
            }

            color currentColor = color::default_color;
            
            if(color_cfg.cfg_data.count(line[i]) > 0) {
               currentColor = color_cfg.cfg_data[line[i]];
            }
            else {
               currentColor = color::default_color;
            }

            color_print(line[i], currentColor);
        }
    }
   }
};

int main(int argc, char* argv[])
{
   if(argc != 3) {
      std::cout << "Usage: vulkanrender.exe <cfg_path> <image_path>" << std::endl;
      return -1;
   }
    cfg cfg_;
    cfg_.load_cfg(argv[1]);
    linuxcolor_t lnx(std::cout, cfg_);
    lnx.image_print(argv[2]);
}