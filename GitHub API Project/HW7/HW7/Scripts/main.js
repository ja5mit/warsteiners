function intial (owner, reponame) {
    $.ajax({
        type: "GET",
        dataType: "json",
        url: "/api/commits?user=" + owner + "&repo=" + reponame,
        success: function (data) { displayCommits(data, owner, reponame); },
        error: errorOnAjax
    });
}

function errorOnAjax() {
        console.log("there was an ERROR in ajax request.");
    }
function displayCommits(data, owner, reponame) {


    if (typeof data.message == "undefined") {

        var titles = "<th> Sha</th> <th> Timestamp </th> <th> Owner </th> <th> Message </th>";
        document.getElementById(reponame).innerHTML += titles;

        for (var commit of data) {

            var trstart = "<tr>";
            var trend = "</tr>";

            var sha = '<td = "block" >' + commit.sha.substring(0, 8); + "</td>";
            var timestamp = '<td = "block" >' + commit.commit.committer.date + "</td>";
            var owner = '<td = "block" >' + commit.commit.committer.name + "</td>";
            var message = '<td = "block" >' + commit.commit.message + "</td>";

            var call = "".concat(trstart, sha, timestamp, owner, message, trend);

            document.getElementById(reponame).innerHTML += call;
        }

    }
    else {

         
             var send ="<tr><td>" +data.message + "</td></tr>";
            document.getElementById(reponame).innerHTML += send;
    }
}






