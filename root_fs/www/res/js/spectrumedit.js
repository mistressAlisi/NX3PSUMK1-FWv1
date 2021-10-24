_spectrumEdit = function(){
    var ctx = false;
    var chart = false;
    var program = [
    ];
    var profile_id = false;
    var profile_name = false;
    var profiles = {};
    var vars = {
        volts: 30,
        br: "#blueRange",
        rr: "#redRange",
        gr: "#greenRange",
        fr: "#farRange",
        pm: "#pomax_alert",
        btn: "#create_btn",
        fmt: "HH:mm",
        tbl: "#editor_table",
        can: "spectrumChart",
        load: "#loadModal",
        prs: "#load_profile",
        src_url: "/api/spec/profiles.json"
    };
    
    this.construct = function(options){
        $.extend(vars , options);
        _initGraph();
        
    };
    
     this.checkModal = function(event){
        p_blue = $(vars["br"])[0].value*vars["volts"];
        b_pct = Math.round(($(vars["br"])[0].value/$(vars["br"])[0].max)*100,2);
        p_red = $(vars["rr"])[0].value*vars["volts"];
        r_pct = Math.round(($(vars["rr"])[0].value/$(vars["rr"])[0].max)*100,2);
        p_green = $(vars["gr"])[0].value*vars["volts"];
        g_pct = Math.round(($(vars["gr"])[0].value/$(vars["gr"])[0].max)*100,2);
        p_far = $(vars["fr"])[0].value*vars["volts"];
        f_pct = Math.round(($(vars["fr"])[0].value/$(vars["fr"])[0].max)*100,2);
        p_total = p_blue+p_red+p_green+p_far;
        $("#db_pct")[0].innerHTML = b_pct;
        $("#dr_pct")[0].innerHTML = r_pct;
        $("#gr_pct")[0].innerHTML = g_pct;
        $("#fr_pct")[0].innerHTML = f_pct;
        $("#watts_total")[0].innerHTML = p_total;
        if (p_total > 1100) {
        $(vars["pm"]).addClass('alert-danger');
        $(vars["btn"]).addClass('bg-danger');
        $(vars["btn"]).disabled = true;
        } else {
        $(vars["pm"]).removeClass('alert-danger');
        $(vars["btn"]).removeClass('bg-danger');
        $(vars["btn"]).disabled = false;
        }
     };
     this._initGraph = function () {
         /** Init chart: **/
        items_b = [];
        items_r = [];
        items_g = [];
        items_f = [];
         ctx = document.getElementById(vars["can"]).getContext('2d');
         chart = new Chart(ctx, {
            type: 'line',    
            options: {
                responsive: true,
                plugins: {
                    title: {
                        display: false,
                        text: 'Spectrum Output'
                    }
                },
                
                scales: {
                    yAxes: [{
                        stacked: true,
                        type: 'linear'
                    }],
                    xAxes: [{
                        type: 'time',
                        time: {
                        unit: 'minute',
                        displayFormats: {
                            'minute': 'HH:mm'
                        }}
                    }]
                }},
            
        data: {
            datasets: [
                {
                label: "Deep Blue",
                data: items_b,
                borderColor: '#4800FF',
                backgroundColor: 'rgba(72,0,255,0.9)',
                },
                {
                label: "Deep Red",
                data: items_r,
                borderColor: '#FF009D',
                backgroundColor: 'rgba(255,0,177,0.5)',
                },
                {
                label: "Green",
                data: items_g,
                borderColor: '#26FF00',
                backgroundColor: 'rgba(38,255,0,0.5)',
                showLine: true
                },
                {
                label: "Far Red",
                data: items_f,
                borderColor: '#FF004D',
                backgroundColor: 'rgba(255,0,77,0.5)',
                showLine: true
                }
                ]}});
//          window.chart = chart;
         $.get(vars["src_url"],function(data,e){

             $(vars["prs"]).empty();
             
             var count = 0;
             var option = new Option("New Profile...",""); $(vars["prs"]).append($(option));
            for (it in data.s) {
                profiles["s_"+data.s[it].i] = "System/"+data.s[it].l;
            if (data.s[it].s == true) { 
                var opt = new Option("System/"+data.s[it].l,"s_"+data.s[it].i,true,true);
            } else {
                var opt = new Option("System/"+data.s[it].l,"s_"+data.s[it].i);
            };
            
            $(vars["prs"])[0].append(opt);
            count =  count + 1;
            }
            for (it in data.u) {
                profiles["u_"+data.u[it].i] = "User/"+data.u[it].l;
            if (data.u[it].s == true) { 
                var opt = new Option("User/"+data.u[it].l,"u_"+data.u[it].i,true,true);
            } else {
                var opt = new Option("User/"+data.u[it].l,"u_"+data.u[it].i);
            };
            
            $(vars["prs"])[0].append(opt);
            count =  count + 1;
            }        
                    
             $(vars["load"]).modal('show');
        program = [];
         });
         
         

     };
     
     /** Function to update entries: **/
     this._editRow = function(event) {;
        
        $("#starttime").datetimepicker('date',moment().format('YYYY/MM/DD '+program[event.data].start));
        $("#endtime").datetimepicker('date',moment().format('YYYY/MM/DD '+program[event.data].end));
        $("#blueRange")[0].value = (program[event.data].b/100)*$("#blueRange")[0].max;
        $("#redRange")[0].value = (program[event.data].r/100)*$("#redRange")[0].max;
        $("#greenRange")[0].value = (program[event.data].g/100)*$("#greenRange")[0].max;
        $("#farRange")[0].value = (program[event.data].f/100)*$("#farRange")[0].max;
        $("#editStep")[0].value = event.data;
        $("#addStepModal").modal('show');
    };
     
     this._updateTable = function() {
         /** This function actually updates the table and the graphs. just made more sense. **/
        
        /** graph variables: **/
        items_b = [];
        items_r = [];
        items_g = [];
        items_f = [];
        /** Table stepper (which also updates items): **/
        $("#append").empty();
        var count = 1;
        for (p in program) {
            

            var tr = $("<tr/>");
            tr.id = "row_"+count;
            $("#append").append(tr);
            var th = $("<th/>").attr({"scope":"row"});
            var edLink = $("<a href/>");
            edLink[0].href = "#_edit_"+count;
            edLink.on('click',count-1,this._editRow);
            
            edLink[0].innerHTML="#"+count;
            th[0].append(edLink[0]);
            tr.append(th);
            var td = $("<td/>");
            td[0].innerHTML = program[p].start;
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].end;
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].b+"%";
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].g+"%";
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].r+"%";
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].f+"%";
            tr.append(td[0]);
            var this_day = new Date();

            var start_time = moment().format("MM/DD/YYYY")+" "+program[p].start;
            var end_time = moment().format("MM/DD/YYYY")+" "+program[p].end;

            items_b.push({"y":program[p].b,"x":start_time});
            items_g.push({"y":program[p].g,"x":start_time});
            items_r.push({"y":program[p].r,"x":start_time});
            items_f.push({"y":program[p].f,"x":start_time});
            items_b.push({"y":program[p].b,"x":end_time});
            items_g.push({"y":program[p].g,"x":end_time});
            items_r.push({"y":program[p].r,"x":end_time});
            items_f.push({"y":program[p].f,"x":end_time});
            count = count +1;
        }
        chart.data.datasets[0].data = items_b;
        chart.data.datasets[1].data = items_r;
        chart.data.datasets[2].data = items_g;
        chart.data.datasets[3].data = items_f;
        chart.update();

     };
     

     
     this.createStep= function(event) {
         $("#time_alert").addClass('d-none');
         start = $('#starttime').datetimepicker('viewDate');
         end = $('#endtime').datetimepicker('viewDate');
         if (start.format(vars["fmt"]) == end.format(vars["fmt"])) {
             $("#time_alert").removeClass('d-none');
            event.preventDefault();
             return false;
         }
         /** Now construct the step object: **/
         step = {
             "start":start.format(vars["fmt"]),
             "end":end.format(vars["fmt"]),
             "b": b_pct,
             "g": g_pct,
             "r": r_pct,
             "f": f_pct
         }
        var editVal = $("#editStep")[0].value;
        if (editVal != "") {
            len = editVal;
            $("#editStep")[0].value = "";
        } else {
            len = program.length;
        };
         program[len] = step;
            
         this._updateTable();
         //event.trigger();
         $("#addStepModal").modal('hide');
         
     };
     
     this.createSpectrum = function(event) {
         s_val = $("#load_profile")[0].value;
         n_val = $("#new-profile")[0].value;
         if ((s_val == "")&&(n_val == "")) {
             alert("Type in a new name or select an existing profile.");
             return false;
         };
         if ((s_val == "") && (n_val.includes(","))) {
             alert("No commas (,) allowed.");
            return false;
         };
         // New Value: 
         if (s_val == "" ) {
             token = n_val.replaceAll(" ","").replace( /\W/g , '');;
             pkeys = Object.keys(profiles);
             window.pkeys = pkeys;
             if(pkeys.includes(token) == true) {
                 alert("Name Already in use; Please type in a different name.");
                 return false;
             };
             
             profiles[token] = n_val;
             profile_id = token;
             profile_name = n_val;
             $("#loadedProfile")[0].value = n_val;
         } else {
             // Existing Value;
             profile_id = s_val;
             profile_name = profiles[profile_id];
             $("#loadedProfile")[0].value = profile_name;
             this.load();
             
         };
        $("#loadModal").modal('hide');
        $("#e_add")[0].disabled = false;
        $("#e_save")[0].disabled = false;
        $("#e_del")[0].disabled = false;
        
            
    };
    /** Load a profile:
     * **/
    this.load = function() {
        if ($(vars["prs"]) == "") { return false; };
        // Is this system or user?
        split = $(vars["prs"])[0].value.split("_");

        if (split[0] == "s") {
            // System (Built in):
            var prefix = "/prb/";
        } else {
            // User:
            var prefix = "/pru/";
        };
        var file = split[1];
        var path = prefix+file+".json";
        $.get(path,function(obj,e){ 
            program = obj.steps;
            profile_id = obj.id;
            profile_name = obj.name;
            window.sEdit._updateTable();

        });
    };
     /**   Load the default profiles index : 
        ** This function also connects the onChange event to the select box:
      **/
     this.loadDefaultsInx= function() {
          $.get("/api/spec/profiles.json",function(data,e){
             $(vars["prs"]).empty();
             profiles = [];
             var option = new Option("Select...",""); $(vars["prs"]).append($(option));
            var count = 0;
             for (it in data.s) {
            profiles[count] = "System/"+data.s[it].l;
            if (data.s[it].s == true) { 
                var opt = new Option("System/"+data.s[it].l,"s_"+data.s[it].i,true,true);
            } else {
                var opt = new Option("System/"+data.s[it].l,"s_"+data.s[it].i);
            };
            $(vars["prs"])[0].append(opt);
            count = count + 1;
            
        };
        for (it in data.u) {
            profiles[count] = "User/"+data.u[it].l;
            if (data.u[it].s == true) { 
                var opt = new Option("User/"+data.u[it].l,"u_"+data.u[it].i,true,true);
            } else {
                var opt = new Option("User/"+data.u[it].l,"u_"+data.u[it].i);
            };
            $(vars["prs"])[0].append(opt);
            count =  count +1;

        };
             
             //$(vars["load"]).modal('show');

         });
        $(vars["prs"]).on("change",this.load);
     };
    /**   Load the user profiles index : 
        ** This function also connects the onChange event to the select box:
      **/
     this.loadUsrInx= function() {
          $.get("/api/spec/usr.json",function(d,e){
             $(vars["prs"]).empty();
             profiles = d.spectrum.profiles;
             var option = new Option("Select...",""); $(vars["prs"]).append($(option));
             for (k in profiles) {
                 var option = new Option(d.spectrum.profiles[k], k); $(vars["prs"]).append($(option));
             };
             
             //$(vars["load"]).modal('show');
         });
        $(vars["prs"]).on("change",this.load);
     };
    /** Serialise the loaded spectrum as a JSON object encoded as a string: **/

    this.saveSpectrum = function(id,name) {
        output = new Object();
        output.type="profile";
        output.id = id;
        output.name = name;
        output.steps = program;
        output.count = program.length;
        return JSON.stringify(output);
    };
    
    /** Exec function for delete: **/
    this._deleteStepExec = function() {
        var val = $("#delete_step")[0].value;
        if (val != "") {
          program.splice(val,1);  
        };
        this._updateTable();
        $("#editStepModal").modal("hide");
    };
    /** Delete a step from the table: **/
    this.deleteStep = function() {
        $("#delete_step").empty();
        var option = new Option("Select...",""); $("#delete_step").append($(option));
        var count = 0;
        for (p in program) {
            var option = new Option("#"+count+": "+program[p].start+"->"+program[p].end, count); $("#delete_step").append($(option));
            count = count+1;
        };
        $("#editStepModal").modal("show");
    };
     
    /** Finally, save a profile: **/
    this.saveProfile = function() {
        if (program.length == 0) {
            alert("At least one step is required.");
            return false;
        };
        $("#pSaved")[0].style.display = 'none';
        $("#profile_name")[0].value = profile_name;
        $("#saveModal").modal('show'); 
    };
    this._saveProfile = function() {
        var n_val = $("#profile_name")[0].value;
        if (n_val.includes(",")) {
            alert("No commas (,) allowed.");
            return false;
         };
        token = n_val.replaceAll(" ","").replace( /\W/g , '');
        
        $("#pid")[0].value = token; 
        $("#pdata")[0].value =  this.saveSpectrum(token,n_val);
        sdata = $("#saveForm").serialize();
        $.post("/api/spec/create.json",sdata, function (data) {
            if (data == "ok") {
                $("#pSaved")[0].style.display = 'block';
                $("#saveModal").modal('hide'); 
            };
        });
    };
};

