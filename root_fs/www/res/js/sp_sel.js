function changeProfile() {
    pdata = $("#profileForm").serialize();
    $.post("/api/spec/set.json",pdata, function (data) {
        $("#confirmModal").modal('hide');
        $("#changeSuccess")[0].style.display = 'block';
    });
};

function loadProfiles() {
    $.getJSON("/api/spec/profiles.json",function(data){
        for (it in data.s) {
            if (data.s[it].s == true) { 
                var opt = new Option("System/"+data.s[it].l,"s_"+data.s[it].i,true,true);
            } else {
                var opt = new Option("System/"+data.s[it].l,"s_"+data.s[it].i);
            };
            $("#loadProfile")[0].append(opt);
            
        };
        for (it in data.u) {
            if (data.u[it].s == true) { 
                var opt = new Option("User/"+data.u[it].l,"u_"+data.u[it].i,true,true);
            } else {
                var opt = new Option("User/"+data.u[it].l,"u_"+data.u[it].i);
            };
            $("#loadProfile")[0].append(opt);

        };
        
    });
};
loadProfiles();
