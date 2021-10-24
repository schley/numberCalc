// #include <cassert>
#include "Logger.hxx"

#include "Parser.hxx"

Aoct::Parser::Parser(Tokens& tokens) : tokens_(tokens)
{
    numberTokens_ = tokens_.size();
    tokenIndex_ = 0;
    
    int tokenCount = 0;
    for (auto& tokenIter : tokens_)
    {
        std::cout << tokenCount++ << " : " << *tokenIter << "\n";
    }
}

Aoct::Parser::~Parser()
{
    tokens_.clear();
}
// bool Aoct::Parser::moreTokens() 
// {
//     bool tokensNotFinished = tokenIndex_ < numberTokens_;
//     return tokensNotFinished;
// }

Aoct::Token::Ptr Aoct::Parser::nextToken()
{
    const std::string LOCATION { "Parser::nextToken (" };
    std::ostringstream logOss;
     
    tokenIndex_++;   

    if (logger_.isDebugEnabled() )
    {
        logOss << LOCATION << __LINE__ << ") tokenIndex_ = " << tokenIndex_
               << "; numberTokens_ = " << numberTokens_;
        logger_.debug(logOss);
    }

    Token::Ptr tokenp = peekToken(); // tokens_[tokenIndex_].get();
    return tokenp;
}

Aoct::Token::Ptr Aoct::Parser::peekToken() 
{
    const std::string LOCATION { "Parser::peekToken (" };
    std::ostringstream logOss;
    if (logger_.isDebugEnabled() )
    {
        logOss << LOCATION << __LINE__ << ") tokenIndex = " << tokenIndex_
               << "; numberTokens = " << numberTokens_;
        logger_.debug(logOss);
    }
    Token::Ptr tokenp = nullptr;
    if (tokenIndex_ < numberTokens_)
    {
        tokenp = tokens_[tokenIndex_].get();
    }
    return tokenp;
}

double Aoct::Parser::unsigned_factor()
{
    const std::string LOCATION {"Parser::unsigned_factor ("};
    std::ostringstream logOss;
    double response = 0;
    Token::Ptr look_ahead = peekToken();
    if (look_ahead == nullptr)
    {
        return response;
    }
    switch (look_ahead->tokenType() ) 
    {
    case TokenType::INTEGER:
    case TokenType::FLOAT:
        response = std::atof(look_ahead->tokenString().c_str() );
        if (logger_.isDebugEnabled() )
        {
            logOss << LOCATION << __LINE__ << ") response = " << response 
                   << "; " << *look_ahead;
            logger_.debug(logOss);
        } 
        look_ahead = nextToken();
        if (look_ahead == nullptr)
        {
            return response;
        }       
        break;

    case TokenType::LEFT_PAREN:
        look_ahead = nextToken();
        if (look_ahead == nullptr)
        {
            return response;
        }
        response = expr();
	look_ahead = peekToken();		   
        if (look_ahead == nullptr)
        {
            return response;
        }
        if (logger_.isDebugEnabled() )
        {
            
        }       
        if (look_ahead->tokenType() != TokenType::RIGHT_PAREN)
	{ 
	    std::string errstr = "missing RIGHT_PAREN ) ";
            errorReport("missing ')'");
        }

        look_ahead = nextToken();
        if (look_ahead == nullptr)
        {
            return response;
        }
        break;

    default:
        std::string errstr = "unexpected token";
        errorReport(errstr);
    }
    return response;
}

double Aoct::Parser::factor()
{
    const std::string LOCATION { "Parser::factor (" };
    double response = 0.0;

    // If there is a leading minus...

    Token::Ptr look_ahead = peekToken();

    if (look_ahead->tokenType() == TokenType::OP_MINUS) 
    {
        look_ahead = nextToken();
        response = -unsigned_factor();
    }
    else
    {
        response = unsigned_factor();
    }
    return response;
}

double Aoct::Parser::term()
{
    const std::string LOCATION { "Parser::term (" };
    std::ostringstream logOss;
    Token::Ptr look_ahead = peekToken();

    if (logger_.isDebugEnabled() )
    {
        logOss << LOCATION << __LINE__ << ") call factor "
               << *look_ahead << "\n";
        logger_.debug(logOss);
    }    

    double response = factor();
    look_ahead = peekToken();
        
    if (logger_.isDebugEnabled() )
    {
        if (look_ahead == nullptr)
        {
            logOss << LOCATION << __LINE__ << ") response = " << response
                   << " after factor with look_ahead == nullptr";
        }
        else
        {
            logOss << LOCATION << __LINE__ << ") response = " << response 
                   << "; " << *look_ahead << "\n";
        }
        logger_.debug(logOss);
    }
    // TokenType currType = look_ahead->getTokenType();

    // while ((look_ahead->getTokenType() == TokenType::OP_MULT) ||
    //        (look_ahead->getTokenType() == TokenType::OP_DIVIDE) ) 
    while (look_ahead != nullptr)
    {
        if (look_ahead->tokenType() == TokenType::OP_MULT) // :
	{
            look_ahead = nextToken(); 
            if (look_ahead == nullptr)
            {
                return response;
            }
            response *= factor(); 
            look_ahead = peekToken();
            continue;
        } 
        if (look_ahead->tokenType() == TokenType::OP_DIVIDE) // 
        {
	    look_ahead = nextToken(); // advance();
            if (look_ahead == nullptr)
            {
                return response;
            }
            response /= factor();
            look_ahead = peekToken();
            continue;
        }
        break;
    }
    return response;
}

double Aoct::Parser::expr()
{
    const std::string LOCATION { "Parser::expr (" };
    std::ostringstream logOss;

    Token::Ptr look_ahead = peekToken();

    if (logger_.isDebugEnabled() )
    {
        logOss << LOCATION << __LINE__ << ") call term " << *look_ahead << "\n";
        logger_.debug(logOss);
    }

    double response = term();

    look_ahead = peekToken();

    if (logger_.isDebugEnabled() && (look_ahead != nullptr))
    {
        logOss << LOCATION << __LINE__ << ") back term " << *look_ahead << "\n";
        logger_.debug(logOss);
    }
    
    // while ((look_ahead->getTokenType() == TokenType::OP_PLUS) ||
    //        (look_ahead->getTokenType() == TokenType::OP_MINUS) )
    while (look_ahead != nullptr)
    {
	if (look_ahead->tokenType() == TokenType::OP_PLUS) 
	{ 
	    look_ahead = nextToken(); // advance();
            if (look_ahead == nullptr)
            {
                return response;
            }
            if (logger_.isDebugEnabled() )
            {
                logOss << LOCATION << __LINE__ << ") OP_PLUS to term";
                logger_.debug(logOss);
            }
            response += term(); 
            look_ahead = peekToken();
            if (look_ahead == nullptr)
            {
                return response;
            }
            continue;
        }
        if (look_ahead->tokenType() == TokenType::OP_MINUS)
	{
	    look_ahead = nextToken(); // advance();
            if (look_ahead == nullptr)
            {
                return response;
            }
            response -= term();
            look_ahead = peekToken();
            continue;
        }
        break;
    }
    return response;
}

void Aoct::Parser::errorReport(std::string errstr)
{
     std::cerr << "ERROR REPORT : " << errstr << "\n";
     // throw ParseEx;
}

