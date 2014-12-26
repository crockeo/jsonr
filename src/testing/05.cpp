#include "05.hpp"

//////////////
// Includes //
#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Testing the empty object.
bool testEmptyObject(const JValue& emptyObject) {
    if (!emptyObject.isObject())
        return true;

    auto map = emptyObject.jObject();
    int n = 0;

    for (auto it = map.begin(); it != map.end(); it++)
        n++;

    if (n > 0)
        return true;

    return false;
}

// Testing the simple object.
bool testSimpleObject(const JValue& simpleObject) {
    if (!simpleObject.isObject())
        return true;

    std::map<std::string, JValue> map = simpleObject.jObject();

    if (map.count("test") == 0)
        return true;

    if (!map["test"].isBool())
        return true;

    if (map["test"].jBool() != true)
        return true;

    return false;
}

// Testing the complex object.
// Complex object structure:
// {
//   "_id": "549c7c943e7a710a50638c11",
//   "index": 0,
//   "guid": "a5847a1e-8897-4195-acd3-82d6270a68a1",
//   "isActive": false,
//   "balance": "$2,495.21",
//   "picture": "http://placehold.it/32x32",
//   "age": 25,
//   "eyeColor": "blue",
//   "name": "Kasey Bentely",
//   "gender": "female",
//   "company": "GINKOGENE",
//   "email": "kaseybentley@ginkogene.com",
//   "phone": "+1 (954) 503-2214",
//   "address": "806 Hull Street, Chalfant, California, 8749",
//   "about": "Sunt officia ex non tempor. Elit voluptate ea est aliquip laboris laborum in eu do elit reprehenderit ea. Irure proident dolore commodo tempor qui. Duis nostrud est reprehenderit ex est culpa commodo mollit excepteur sunt ex qui. Lorem id consectetur qui mollit. Anim commodo laborum eu do ea dolor laboris in proident Lorem sint anim.\r\n",
//   "registered": "2014-10-21T10:42:13 +04:00",
//   "latitude": 48.984494,
//   "longitude": -81.8415,
//   "tags": ["incididunt", "eu", "eiusmod", "nostrud", "tempor", "incididunt", "consectetur"],
//   "friends": [{ "id": 0, "name": "Snow Williamson" }, { "id": 1, "name": "Christy Mcfadden" }, { "id": 2, "name": "Cathy Stone" }],
//   "greeting": "Hello, Kasey Bentley! You have 6 unread messages.",
//   "favoriteFruit": "strawberry"
// }
bool testComplexObject(const JValue& complexObject) {
    if (!complexObject.isObject())
        return true;

    // TODO: Some actual testing here.

    return false;
}

// Attempting to test parseJSON for 'null' values.
int runTest05() {
    JValue emptyObject = parseJSON("{ }");
    JValue simpleObject = parseJSON("{ \"test\": true }");
    JValue complexObject = parseJSON("{ \"_id\": \"549c7c943e7a710a50638c11\", \"index\": 0, \"guid\": \"a5847a1e-8897-4195-acd3-82d6270a68a1\", \"isActive\": false, \"balance\": \"$2,495.21\", \"picture\": \"http://placehold.it/32x32\", \"age\": 25, \"eyeColor\": \"blue\", \"name\": \"Kasey Bentley\", \"gender\": \"female\", \"company\": \"GINKOGENE\", \"email\": \"kaseybentley@ginkogene.com\", \"phone\": \"+1 (954) 503-2214\", \"address\": \"806 Hull Street, Chalfant, California, 8749\", \"about\": \"Sunt officia ex non tempor. Elit voluptate ea est aliquip laboris laborum in eu do elit reprehenderit ea. Irure proident dolore commodo tempor qui. Duis nostrud est reprehenderit ex est culpa commodo mollit excepteur sunt ex qui. Lorem id consectetur qui mollit. Anim commodo laborum eu do ea dolor laboris in proident Lorem sint anim.\\r\\n\", \"registered\": \"2014-10-21T10:42:13 +04:00\", \"latitude\": 48.984494, \"longitude\": -81.8415, \"tags\": [ \"incididunt\", \"eu\", \"eiusmod\", \"nostrud\", \"tempor\", \"incididunt\", \"consectetur\" ], \"friends\": [ { \"id\": 0, \"name\": \"Snow Williamson\" }, { \"id\": 1, \"name\": \"Christy Mcfadden\" }, { \"id\": 2, \"name\": \"Cathy Stone\" } ], \"greeting\": \"Hello, Kasey Bentley! You have 6 unread messages.\", \"favoriteFruit\": \"strawberry\" }");

    if (testEmptyObject(emptyObject))
        return 1;
    if (testSimpleObject(simpleObject))
        return 1;
    if (testComplexObject(complexObject))
        return 1;

    return 0;
}
