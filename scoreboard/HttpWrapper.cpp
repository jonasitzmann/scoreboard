#include "HttpWrapper.h"


HttpWrapper::HttpWrapper():
	logger(LoggerFactory::getLogger())
{	
	https = std::make_shared<HTTPClient>();
	fingerprint = "f93c6d736c61121d5c1bb7af829b9eb45846673b";
  logger.log("certificate valid until ‎Sonntag, ‎12. ‎August ‎2018 20:02:05");
	https->addHeader("Accept", "application/json", true);
	https->addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjRlNDE3Yjg3NGNkYzQ3YTdhNzA4ODE1OGIwZTBmZDY3MDc2MWIyYTc1OGQyODRhOTU3YTJjMjViMTIzNzk3MzRmZWZhMGU4NzQ0ZmQwNmNlIn0.eyJhdWQiOiI0IiwianRpIjoiNGU0MTdiODc0Y2RjNDdhN2E3MDg4MTU4YjBlMGZkNjcwNzYxYjJhNzU4ZDI4NGE5NTdhMmMyNWIxMjM3OTczNGZlZmEwZTg3NDRmZDA2Y2UiLCJpYXQiOjE1MjI4NzU3MjYsIm5iZiI6MTUyMjg3NTcyNiwiZXhwIjoxNTU0NDExNzI2LCJzdWIiOiIxMyIsInNjb3BlcyI6W119.eOS0o2mM03I-di8mNW9fO2NRsxpXoC_yj5akmV6AnAVF0yfzHnstWIhC0X8pKgeE7_kHsWc3TGS6rtu_BiUuIk48jlrpFHWOUWGuLpZPRRjcgqkqOqsWX6q97juAdUcBBDwJmdamWDy_XQ7xTqGd5qLAQtKSDJFDgVLjNnk7Y7w5j4lwY9bwhoxjELPBisb1WwCRDaAydOf1QoZPBe-p2xfNb87EK1jTqiYKO_bJGo54JW-a_5359_RQr3-3pVn8KP_tzZuPyyZHGBJh-ioLkYJ_bPjN_oTwOYVZslF_fppx4wXPBmBgiOa4XYRjSxiO5r7P1pwdrpDx8SClbcZw78XRW8R79K-tp-ofsZAiNxfl80ShWVjJ4P7z4IX6e-Z5zYQEjgAIRhPkfONsntESLS3fvwdX_RO6Ne203iot74IjmMHKR2OfIKerCxEs8_5o_ZtgDkrkqRljtKKBruAbpBNa2xwSCEIk7uiQu7WWbZL24mMakpNNpWorMxc1PeOcHu0SMhWXRW6glhHBfOwDZLHOp-JSkcd4okImc_z5Oga0N17C25XFEgFjii1lO7FRFvtcexCn88CXFzHqLTIOtYYYb_a_PktftKBgSjjwXr2GWcEKVddErXlwYp3DeIKdbt1p6UFcoAMHB21PeEiRnpLo_hYvqXG3MWXS4e8OCmk");
	https->addHeader("Content-Type", "application/x-www-form-urlencoded");
}


HttpWrapper::~HttpWrapper()
{
}

bool HttpWrapper::begin()
{
	return true;
}

std::string HttpWrapper::sendRequest(std::string method, std::string url, std::string payload)
{
	std::string received;
	https->begin(String(url.c_str()), String(fingerprint.c_str()));
  logger.log("url: ");
  logger.log(method.c_str());
	logger.log("method: ");
  logger.log(url.c_str());
  logger.log("payload: ");
  logger.log(payload.c_str());
	int httpCode = https->sendRequest(method.c_str(), String(payload.c_str()));
	if (httpCode > 0) {
		received = std::string(https->getString().c_str());
	}
	else {
		std::string errStr = "HTTP error: " + std::string(https->errorToString(httpCode).c_str());
		logger.log(errStr);
	}
	https->end();
	return received;
}

std::string HttpWrapper::getString()
{
	return std::string();
}

std::string HttpWrapper::errorToString(int code)
{
	return std::string();
}
