#if !defined __AOCT_TOKEN_TYPE_HXX__
#define      __AOCT_TOKEN_TYPE_HXX__

#include <iostream>
#include <memory>

namespace Aoct
{
    enum class TokenType : int
    {
        UNDEFINED = 0,
        OP_PLUS,
	OP_MULT,
        OP_DIVIDE,
        OP_MINUS,
	FLOAT, 
        INTEGER, 
        LEFT_PAREN,
        RIGHT_PAREN,
        // END_INPUT,
        SEMICOLON,

        // assumed number token types
        // 
        NUMBER_TOKENS
    }; 

    class TokenProperty
    {
    public:
        TokenProperty() = delete;
        TokenProperty(TokenType type, std::string typestr, std::string regexp);
        ~TokenProperty();
        TokenType tokenType() const;
        std::string tokenTypeString() const;
        std::string tokenRegex() const;
        using UPtr = std::unique_ptr<TokenProperty>;
    private:
        TokenType tokenType_;
        std::string tokenTypeString_;
        std::string tokenRegex_;
    };

    // using TokenProperties = std::map<TokenType, TokenProperty::UPtr>;
    using TokenProperties = std::array<TokenProperty::UPtr, 
                                       (int) TokenType::NUMBER_TOKENS>; 

} // namespace Aoct

#endif    // __AOCT_TOKEN_TYPES_HXX__
