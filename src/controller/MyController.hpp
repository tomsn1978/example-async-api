
#ifndef MyController_hpp
#define MyController_hpp

#include "dto/MyDTOs.hpp"
#include "service/DataService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"


#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin codegen

/**
 *  EXAMPLE ApiController
 *  Basic examples of howto create ENDPOINTs
 *  More details on oatpp.io
 */
class MyController : public oatpp::web::server::api::ApiController {
  typedef oatpp::web::protocol::http::Status Status;
protected:
  MyController(const std::shared_ptr<ObjectMapper>& objectMapper)
  : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
   typedef MyController __ControllerType;
   DataService m_dataService;
  static oatpp::String loadFile(const char* filename) {
    auto buffer = oatpp::String::loadFromFile(filename);
    OATPP_ASSERT_HTTP(buffer, Status::CODE_404, "File Not Found:(");
    return buffer;
  }
public:
  
  /**
   *  Inject @objectMapper component here as default parameter
   *  Do not return bare Controllable* object! use shared_ptr!
   */
  static std::shared_ptr<MyController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                                                    objectMapper)){
    return std::shared_ptr<MyController>(new MyController(objectMapper));
  }
  

ENDPOINT_ASYNC("GET", "/", Root) {

    ENDPOINT_ASYNC_INIT(Root)

    Action act() override {
      
      static auto fileCache = loadFile("webres/meter/index.html");
      auto response = controller->createResponse(Status::CODE_200, fileCache);
      response->putHeader(Header::CONTENT_TYPE, "text/html");
      return _return(response);
    }

  };

ENDPOINT_ASYNC("GET", "/pages/instantaneous.html", instantaneous) {

    ENDPOINT_ASYNC_INIT(instantaneous)

    Action act() override {
      
      static auto fileCache = loadFile("webres/meter//pages/instantaneous.html");
      auto response = controller->createResponse(Status::CODE_200, fileCache);
      response->putHeader(Header::CONTENT_TYPE, "text/html");
      return _return(response);
    }

  };



  ENDPOINT_ASYNC("GET", "/pages/instantaneous/{classid}/{obis}/{attr}", readinstan) {

    ENDPOINT_ASYNC_INIT(readinstan)

    Action act() override {
      Status status = Status::CODE_200;
    String errmsg;

      oatpp::UInt32 classid = atoi(request->getPathVariable("classid")->c_str());
      String obis = request->getPathVariable("obis");
      oatpp::UInt32 attr = atoi(request->getPathVariable("attr")->c_str());

      auto frd=controller->m_dataService.readurl(classid,obis,attr,status,errmsg);
      return _return(controller->createDtoResponse(Status::CODE_200, frd));
      



     
      
    }

  };
















ENDPOINT_ASYNC("GET", "/pages/firmware.html", firmware) {

    ENDPOINT_ASYNC_INIT(firmware)

    Action act() override {
      
      static auto fileCache = loadFile("webres/meter//pages/firmware.html");
      auto response = controller->createResponse(Status::CODE_200, fileCache);
      response->putHeader(Header::CONTENT_TYPE, "text/html");
      return _return(response);
    }

  };

  ENDPOINT_ASYNC("GET", "/pages/loadprofile.html", loadprofile) {

    ENDPOINT_ASYNC_INIT(loadprofile)

    Action act() override {
      
      static auto fileCache = loadFile("webres/meter//pages/loadprofile.html");
      auto response = controller->createResponse(Status::CODE_200, fileCache);
      response->putHeader(Header::CONTENT_TYPE, "text/html");
      return _return(response);
    }

  };





















  ENDPOINT_ASYNC("POST", "/data", getrequest){
      ENDPOINT_ASYNC_INIT(getrequest)

          Action act() override{
              //OATPP_LOGD("UserController", "get data");
              return request->readBodyToDtoAsync<oatpp::Object<dlmsDto>>(
                    controller->getDefaultObjectMapper())
              .callbackTo(&getrequest::getread);
  }

  Action getread(const oatpp::Object<dlmsDto> &data)
  {
    Status status = Status::CODE_200;
    String errmsg;

    //OATPP_LOGD("UserController", "raed");
    auto mess = controller->m_dataService.readdata(data->classid, data->obis, data->attribute, status, errmsg);
    if (status != Status::CODE_200)
    {
      auto response = controller->createResponse(status, errmsg);
      response->putHeaderIfNotExists("Content-Type", "application/json");
      return _return(response);
    }
    return _return(controller->createDtoResponse(Status::CODE_200, mess));
  }
  }
  ;

  ENDPOINT_ASYNC("GET", "/index", Rootindex){

      ENDPOINT_ASYNC_INIT(Rootindex)

          Action act() override{

              static auto fileCache = loadFile("webres/front/index.html");
  auto response = controller->createResponse(Status::CODE_200, fileCache);
  response->putHeader(Header::CONTENT_TYPE, "text/html");
  return _return(response);
    }

  };


  
  /**
   *  Echo body endpoint Coroutine. Mapped to "/body/string".
   *  Returns body received in the request
   */
  ENDPOINT_ASYNC("GET", "/body/string", EchoStringBody) {
    
    ENDPOINT_ASYNC_INIT(EchoStringBody)
    
    Action act() override {
      /* return Action to start child coroutine to read body */
      return request->readBodyToStringAsync().callbackTo(&EchoStringBody::returnResponse);
    }
    
    Action returnResponse(const oatpp::String& body){
      /* return Action to return created OutgoingResponse */
      return _return(controller->createResponse(Status::CODE_200, body));
    }
    
  };
  
  /**
   *  Echo body endpoint Coroutine. Mapped to "/body/dto".
   *  Deserialize DTO reveived, and return same DTO
   *  Returns body as MessageDto received in the request
   */
  ENDPOINT_ASYNC("GET", "/body/dto", EchoDtoBody) {
    
    ENDPOINT_ASYNC_INIT(EchoDtoBody)
    
    Action act() override {

      return request->readBodyToDtoAsync<oatpp::Object<MessageDto>>(controller->getDefaultObjectMapper()).callbackTo(&EchoDtoBody::returnResponse);
    }
    
    Action returnResponse(const oatpp::Object<MessageDto>& body){
      return _return(controller->createDtoResponse(Status::CODE_200, body));
    }
    
  };
  
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- End codegen

#endif /* MyController_hpp */
