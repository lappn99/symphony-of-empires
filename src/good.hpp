#ifndef GOOD_HPP
#define GOOD_HPP

typedef uint8_t GoodId;
/**
* A good, mostly serves as a "product type"
 */
class Good {
public:
    using Id = uint16_t;

    std::string name = "default";
    std::string ref_name = "default";

    // Determines if the good can be "eaten", this makes the product fullfill a life need
    bool is_edible;
};

#endif