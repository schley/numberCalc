#if !defined __AOCT_PARSER_HXX__
#define      __AOCT_PARSER_HXX__

#include "Logger.hxx"
#include "Token.hxx"

namespace Aoct
{
    class Parser
    {
    public:
        explicit Parser(Tokens& tokens);
        ~Parser();

        Token::Ptr nextToken(); // advance
        Token::Ptr peekToken();

        double unsigned_factor(); 
        double factor();
        double term();
        double expr();

        void errorReport(std::string errorstring);
    private:
        Tokens& tokens_;
        int numberTokens_;
        int tokenIndex_;

        Logger logger_;
    };

} // namespace Aoct

#endif // __AOCT_PARSER_HXX__
