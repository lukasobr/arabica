//////////////////////////////////////////////////
//
// An example application which generates PYX notation.
// It's a pretty literal translation of the Sean McGrath's
// sax2pyx.py code presented in his XML Processing In Python book.
//
// For more information on PYX see http://pyxie.sourceforce.net/
//
// $Id$
//
//////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <SAX/helpers/DefaultHandler.h>
#include <SAX/InputSource.h>
#include <SAX/XMLReader.h>
#include <iostream>

class SAX2PYX : public SAX::DefaultHandler
{
  public:
    virtual void startElement(const std::string& namespaceURI, const std::string& localName,
                              const std::string& qName, const SAX::Attributes& atts);
    virtual void endElement(const std::string& namespaceURI, const std::string& localName,
                            const std::string& qName);
    virtual void characters(const std::string& ch);
    virtual void processingInstruction(const std::string& target, const std::string& data);

    virtual void warning(const SAX::SAXParseException& e) { fatalError(e); }
    virtual void error(const SAX::SAXParseException& e) { fatalError(e); }

    void setParser(SAX::XMLReader<std::string>& parser) { parser_ = &parser; }

  private:
    std::string escape(const std::string& str) const;
    SAX::XMLReader<std::string>* parser_;
}; // class SimpleHandler

int main(int argc, char* argv[])
{
  if(argc == 1) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc == 0)

  SAX2PYX handler;

  for(int i = 1; i < argc; ++i)
  {
    try
    {
      SAX::XMLReader<std::string> myParser;
      myParser.setContentHandler(handler);
      myParser.setErrorHandler(handler);
      handler.setParser(myParser);

      SAX::InputSource is(argv[i]);
      myParser.parse(is);
    } // try
    catch(std::runtime_error& e)
    {
      std::cerr << "Parse problem " << e.what() << std::endl;
    } // catch  
  } // for ...

  return 0;
} // main


void SAX2PYX::startElement(const std::string&, const std::string& localName,
                           const std::string&, const SAX::Attributes& atts)
{
  std::cout << '(' << localName << std::endl;

  for(int i = 0; i < atts.getLength(); ++i)
  {
    std::cout << 'A' << atts.getLocalName(i)
              << ' ' << escape(atts.getValue(i))
              << std::endl;
  } // for ...

  std::cerr << "             " 
            << parser_->getLineNumber() 
            << ","
            << parser_->getColumnNumber() 
	    << std::endl;
} // startElement

void SAX2PYX::endElement(const std::string&, const std::string& localName,
                       const std::string&)
{
  std::cout << ')' << localName << std::endl;
} // endElement

void SAX2PYX::characters(const std::string& ch)
{
  std::cout << '-' << escape(ch) << std::endl;
} // characters

void SAX2PYX::processingInstruction(const std::string& target, const std::string& data)
{
  std::cout << '?' << target
            << ' ' << data << std::endl;
} // processingInstruction

std::string SAX2PYX::escape(const std::string& str) const
{
  std::string estr(str);
  std::string::size_type i(estr.find("\n"));
  while(i != std::string::npos)
  {
    estr.replace(i, 1, "\\n", 2);
    i = estr.find("\n", i);
  } // while ...
  return estr;
} // escape

// end of file
