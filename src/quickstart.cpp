#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using namespace std;

string url_encode(const string &value) {
  ostringstream escaped;
  escaped.fill('0');
  escaped << hex;

  for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
      string::value_type c = (*i);

      // Keep alphanumeric and other accepted characters intact
      if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
          escaped << c;
          continue;
      }

      // Any other characters are percent-encoded
      escaped << uppercase;
      escaped << '%' << setw(2) << int((unsigned char) c);
      escaped << nouppercase;
  }

  return escaped.str();
}

int main()
{
  try
  {
    
    // Create an instance.
    mongocxx::instance inst{};

    const auto uri = mongocxx::uri{"mongodb+srv://dbuser:OZJ6WM0qdNh7qJAZ@cluster0.vvhyy.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"};

    // Set the version of the Stable API on the client
    mongocxx::options::client client_options;
    const auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
    client_options.server_api_opts(api);

    // Setup the connection and get a handle on the "admin" database.
    mongocxx::client conn{ uri, client_options };
    mongocxx::database db = conn["admin"];

    // Ping the database.
    const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
    db.run_command(ping_cmd.view());
    std::cout << "Pinged your deployment. You successfully connected to MongoDB!" << std::endl;
  }
  catch (const std::exception& e)
  {
    // Handle errors
    std::cout<< "Exception: " << e.what() << std::endl;
  }

  return 0;
}