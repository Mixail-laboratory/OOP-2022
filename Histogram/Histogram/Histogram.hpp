#ifndef HISTOGRAM_HISTOGRAM_HPP
#define HISTOGRAM_HISTOGRAM_HPP

#include <map>
#include <unordered_map>
#include <istream>
#include <vector>


class Histogram final {
public:
    Histogram() = default;
    Histogram(const std::vector<std::string>& vector);
    Histogram(std::istream& istream);
    Histogram(const Histogram& other) = default;

    auto begin(){
        return histrogram.begin();
    }

    auto end(){
        return histrogram.end();
    }

    const auto cbegin() const{
        return histrogram.cbegin();
    }

    const auto cend() const{
        return histrogram.cend();
    }

    bool operator==(const Histogram& other) const;

    Histogram operator+(const Histogram& other) const;

    Histogram operator-(const Histogram& other) const;

    void addWord(const std::string& word);

    const int getFrequency(const std::string& word) const;
private:
    std::unordered_map<std::string , int> histrogram;

};


#endif //HISTOGRAM_HISTOGRAM_HPP
