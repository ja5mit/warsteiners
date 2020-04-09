using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace HW7.Models.ViewModels
{
    public class Details
    {
        public string fullname { get; set; }
        public string user { get; set; }
        public string email { get; set; }
        public string picture { get; set; }
        public string reposurl { get; set; }
        public List<Repo> ReposList { get; set; }

    }
}