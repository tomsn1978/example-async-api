
#ifndef MyDTOs_hpp
#define MyDTOs_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class HelloDto : public oatpp::DTO {
  
  DTO_INIT(HelloDto, DTO)
  
  DTO_FIELD(String, userAgent, "user-agent");
  DTO_FIELD(String, message);
  DTO_FIELD(String, server);
  
};

class MessageDto : public oatpp::DTO {
  
  DTO_INIT(MessageDto, DTO)
  
  DTO_FIELD(String, message);
  
};

class dlmsDto : public oatpp::DTO {
  
  DTO_INIT(dlmsDto, DTO)
  DTO_FIELD(UInt32, classid);
  DTO_FIELD(String, obis);
  DTO_FIELD(UInt32, attribute);
  
};



#include OATPP_CODEGEN_END(DTO)

#endif /* MyDTOs_hpp */
