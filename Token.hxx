#if !defined __AOCT_TOKEN_HXX__
#define      __AOCT_TOKEN_HXX__

#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <regex>

#include "TokenType.hxx"

namespace Aoct
{
    class Token
    {
        public:
            Token() = delete;
            Token(std::string tokenstring, TokenType type);
            ~Token();
		
	    std::string tokenString() const;
	    TokenType tokenType() const;	
            std::string tokenTypeString(TokenType type) const;

            using UPtr = std::unique_ptr<Token>;
            using Ptr = Token*;

            static std::string match_separators();
            static UPtr factory(std::string tokenString);

            void print(std::ostream& tokenOss) const;
        private:
            // tokenProperties() method is class method (static) because 
            // class method factory above relies on tokenProperties method.
            //
            static TokenProperties& tokenProperties();
            std::string tokenString_;
            TokenType tokenType_;
    }; // class Token

    using Tokens = std::vector<Token::UPtr>;

} // namespace Aoct 

std::ostream& operator<<(std::ostream& tokenOss, const Aoct::Token& token);

#endif    // __AOCT_TOKEN_HXX__

