using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using HW7.Models.ViewModels;

namespace HW7.Controllers
{
    public class HomeController : Controller
    {
        readonly string username = "ja5mit";
        readonly string credentials = System.IO.File.ReadAllText(AppDomain.CurrentDomain.BaseDirectory + "info.tkn");

        public ActionResult Index()

        {
          
            string uri = "https://api.github.com/user";
            string json = SendRequest(uri, credentials, username);
            JObject info = JObject.Parse(json);

            Details d = new Details();
            {
                //Basic details that go in first box
                d.fullname = (string)info["name"];
                d.user = (string)info["login"];
                d.email = (string)info["email"];
                d.picture = (string)info["avatar_url"];
                d.reposurl = "https://api.github.com/user/repos";
            }
            string reposjson = SendRequest(d.reposurl, credentials, username);
            JArray repoarray = JArray.Parse(reposjson);

            d.ReposList = new List<Repo>();

            for (int i = 0; i < repoarray.Count; ++i)
            {
                Repo obj = new Repo();
                {
                    obj.reponame = repoarray[i]["name"].ToString();
                    obj.owner = repoarray[i]["owner"]["login"].ToString();
                    obj.ownerpic = repoarray[i]["owner"]["avatar_url"].ToString();
                    obj.updated = repoarray[i]["updated_at"].ToString();
                    obj.commitsurl = "https://api.github.com/repos/" + repoarray[i]["full_name"] + "/" + "commits";

                }
                d.ReposList.Add(obj);

            }


            return View(d);
        }
        public ActionResult Commits()
        {
          


            string owner = Request.QueryString["user"];
            string reponame = Request.QueryString["repo"];
            string commitsurl = "https://api.github.com/repos/"+ owner + "/"+ reponame + "/commits";
            string commitsjson = SendRequest(commitsurl, credentials, username);
            JToken commitdata = JContainer.Parse(commitsjson);




            return new ContentResult
            {
                Content = JsonConvert.SerializeObject(commitdata),
                ContentType = "application/json",
                ContentEncoding = System.Text.Encoding.UTF8
            };
        }

        private string SendRequest(string uri, string credentials, string username)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(uri);
            request.Headers.Add("Authorization", "token " + credentials);
            request.UserAgent = username;       // Required, see: https://developer.github.com/v3/#user-agent-required
            request.Accept = "application/json";

            string jsonString = "{\"message\": \"no commits in this repo\"}";
            // TODO: You should handle exceptions here
            try
            {
                using (WebResponse response = request.GetResponse())
                {
                    Stream stream = response.GetResponseStream();
                    StreamReader reader = new StreamReader(stream);
                    jsonString = reader.ReadToEnd();
                    reader.Close();
                    stream.Close();
                }
            }
            catch (WebException e)
            {
                System.Diagnostics.Debug.WriteLine(e.Message);
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.Message);
            }
            return jsonString;
        }
    }
}