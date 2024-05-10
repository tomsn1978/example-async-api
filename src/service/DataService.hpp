


#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"
#include "../dto/MyDTOs.hpp"


class DataService {
private:
  typedef oatpp::web::protocol::http::Status Status;
public:

      oatpp::Object<MessageDto> readdata( const oatpp::UInt32& classid,const oatpp::String& obis,const oatpp::UInt32& attr,
      Status &status, oatpp::String& errmsg) const {

        auto message = oatpp::Object<MessageDto>::createShared();

        message->message="hello word:"+obis;

        return message;
}


      oatpp::Object<MessageDto> readurl( const oatpp::UInt32& classid,const oatpp::String& obis,const oatpp::UInt32& attr,
      Status &status, oatpp::String& errmsg) const {

        auto message = oatpp::Object<MessageDto>::createShared();

        message->message="hello word:"+obis;

        return message;
}
};  