
// Generated from src/bpm/Traces.g by ANTLR 4.9.2


#include "TracesLexer.h"


using namespace antlr4;


TracesLexer::TracesLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

TracesLexer::~TracesLexer() {
  delete _interpreter;
}

std::string TracesLexer::getGrammarFileName() const {
  return "Traces.g";
}

const std::vector<std::string>& TracesLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& TracesLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& TracesLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& TracesLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& TracesLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> TracesLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& TracesLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> TracesLexer::_decisionToDFA;
atn::PredictionContextCache TracesLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN TracesLexer::_atn;
std::vector<uint16_t> TracesLexer::_serializedATN;

std::vector<std::string> TracesLexer::_ruleNames = {
  "T__0", "T__1", "T__2", "T__3", "T__4", "VAR", "LABEL", "INTNUMBER", "NUMBER", 
  "STRING", "SPACE", "COMMENT", "LINE_COMMENT"
};

std::vector<std::string> TracesLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> TracesLexer::_modeNames = {
  "DEFAULT_MODE"
};

std::vector<std::string> TracesLexer::_literalNames = {
  "", "';'", "':'", "'{'", "'}'", "'='"
};

std::vector<std::string> TracesLexer::_symbolicNames = {
  "", "", "", "", "", "", "VAR", "LABEL", "INTNUMBER", "NUMBER", "STRING", 
  "SPACE", "COMMENT", "LINE_COMMENT"
};

dfa::Vocabulary TracesLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> TracesLexer::_tokenNames;

TracesLexer::Initializer::Initializer() {
  // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x2, 0xf, 0x68, 0x8, 0x1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 
       0x4, 0x4, 0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 
       0x7, 0x9, 0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 
       0x9, 0xa, 0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 
       0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
       0x7, 0x6, 0x7, 0x29, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x2a, 0x3, 0x8, 
       0x3, 0x8, 0x7, 0x8, 0x2f, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x32, 0xb, 
       0x8, 0x3, 0x9, 0x6, 0x9, 0x35, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 0x36, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x3c, 0xa, 0xa, 0x3, 0xb, 
       0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x42, 0xa, 0xb, 0xc, 0xb, 
       0xe, 0xb, 0x45, 0xb, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x6, 0xc, 
       0x4a, 0xa, 0xc, 0xd, 0xc, 0xe, 0xc, 0x4b, 0x3, 0xc, 0x3, 0xc, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0x54, 0xa, 0xd, 0xc, 
       0xd, 0xe, 0xd, 0x57, 0xb, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 
       0x62, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x65, 0xb, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0x55, 0x2, 0xf, 0x3, 0x3, 0x5, 0x4, 0x7, 0x5, 0x9, 0x6, 
       0xb, 0x7, 0xd, 0x8, 0xf, 0x9, 0x11, 0xa, 0x13, 0xb, 0x15, 0xc, 0x17, 
       0xd, 0x19, 0xe, 0x1b, 0xf, 0x3, 0x2, 0x6, 0x4, 0x2, 0x43, 0x5c, 0x63, 
       0x7c, 0x4, 0x2, 0x24, 0x24, 0x5e, 0x5e, 0x4, 0x2, 0xb, 0xc, 0x22, 
       0x22, 0x4, 0x2, 0xc, 0xc, 0xf, 0xf, 0x2, 0x70, 0x2, 0x3, 0x3, 0x2, 
       0x2, 0x2, 0x2, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2, 0x7, 0x3, 0x2, 0x2, 
       0x2, 0x2, 0x9, 0x3, 0x2, 0x2, 0x2, 0x2, 0xb, 0x3, 0x2, 0x2, 0x2, 
       0x2, 0xd, 0x3, 0x2, 0x2, 0x2, 0x2, 0xf, 0x3, 0x2, 0x2, 0x2, 0x2, 
       0x11, 0x3, 0x2, 0x2, 0x2, 0x2, 0x13, 0x3, 0x2, 0x2, 0x2, 0x2, 0x15, 
       0x3, 0x2, 0x2, 0x2, 0x2, 0x17, 0x3, 0x2, 0x2, 0x2, 0x2, 0x19, 0x3, 
       0x2, 0x2, 0x2, 0x2, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x3, 0x1d, 0x3, 0x2, 
       0x2, 0x2, 0x5, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x7, 0x21, 0x3, 0x2, 0x2, 
       0x2, 0x9, 0x23, 0x3, 0x2, 0x2, 0x2, 0xb, 0x25, 0x3, 0x2, 0x2, 0x2, 
       0xd, 0x28, 0x3, 0x2, 0x2, 0x2, 0xf, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x11, 
       0x34, 0x3, 0x2, 0x2, 0x2, 0x13, 0x38, 0x3, 0x2, 0x2, 0x2, 0x15, 0x3d, 
       0x3, 0x2, 0x2, 0x2, 0x17, 0x49, 0x3, 0x2, 0x2, 0x2, 0x19, 0x4f, 0x3, 
       0x2, 0x2, 0x2, 0x1b, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x7, 0x3d, 
       0x2, 0x2, 0x1e, 0x4, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x7, 0x3c, 0x2, 
       0x2, 0x20, 0x6, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x7, 0x7d, 0x2, 0x2, 
       0x22, 0x8, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 0x7f, 0x2, 0x2, 0x24, 
       0xa, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x7, 0x3f, 0x2, 0x2, 0x26, 0xc, 
       0x3, 0x2, 0x2, 0x2, 0x27, 0x29, 0x4, 0x63, 0x7c, 0x2, 0x28, 0x27, 
       0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 
       0x2, 0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2b, 0xe, 0x3, 0x2, 
       0x2, 0x2, 0x2c, 0x30, 0x4, 0x43, 0x5c, 0x2, 0x2d, 0x2f, 0x9, 0x2, 
       0x2, 0x2, 0x2e, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x32, 0x3, 0x2, 0x2, 
       0x2, 0x30, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 
       0x31, 0x10, 0x3, 0x2, 0x2, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x33, 
       0x35, 0x4, 0x32, 0x3b, 0x2, 0x34, 0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 
       0x36, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 
       0x3, 0x2, 0x2, 0x2, 0x37, 0x12, 0x3, 0x2, 0x2, 0x2, 0x38, 0x3b, 0x5, 
       0x11, 0x9, 0x2, 0x39, 0x3a, 0x7, 0x30, 0x2, 0x2, 0x3a, 0x3c, 0x5, 
       0x11, 0x9, 0x2, 0x3b, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 0x3, 
       0x2, 0x2, 0x2, 0x3c, 0x14, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x43, 0x7, 0x24, 
       0x2, 0x2, 0x3e, 0x42, 0xa, 0x3, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x5e, 
       0x2, 0x2, 0x40, 0x42, 0x9, 0x3, 0x2, 0x2, 0x41, 0x3e, 0x3, 0x2, 0x2, 
       0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x42, 0x45, 0x3, 0x2, 0x2, 0x2, 
       0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x3, 0x2, 0x2, 0x2, 0x44, 
       0x46, 0x3, 0x2, 0x2, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 
       0x7, 0x24, 0x2, 0x2, 0x47, 0x16, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4a, 
       0x9, 0x4, 0x2, 0x2, 0x49, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x3, 
       0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x3, 0x2, 
       0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x8, 0xc, 0x2, 
       0x2, 0x4e, 0x18, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x31, 0x2, 
       0x2, 0x50, 0x51, 0x7, 0x2c, 0x2, 0x2, 0x51, 0x55, 0x3, 0x2, 0x2, 
       0x2, 0x52, 0x54, 0xb, 0x2, 0x2, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 
       0x54, 0x57, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 0x2, 0x2, 0x2, 0x55, 
       0x53, 0x3, 0x2, 0x2, 0x2, 0x56, 0x58, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 
       0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x7, 0x2c, 0x2, 0x2, 0x59, 0x5a, 
       0x7, 0x31, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 
       0x8, 0xd, 0x2, 0x2, 0x5c, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x7, 
       0x31, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0x31, 0x2, 0x2, 0x5f, 0x63, 0x3, 
       0x2, 0x2, 0x2, 0x60, 0x62, 0xa, 0x5, 0x2, 0x2, 0x61, 0x60, 0x3, 0x2, 
       0x2, 0x2, 0x62, 0x65, 0x3, 0x2, 0x2, 0x2, 0x63, 0x61, 0x3, 0x2, 0x2, 
       0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0x66, 0x3, 0x2, 0x2, 0x2, 
       0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x8, 0xe, 0x2, 0x2, 0x67, 
       0x1c, 0x3, 0x2, 0x2, 0x2, 0xc, 0x2, 0x2a, 0x30, 0x36, 0x3b, 0x41, 
       0x43, 0x4b, 0x55, 0x63, 0x3, 0x8, 0x2, 0x2, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

TracesLexer::Initializer TracesLexer::_init;
