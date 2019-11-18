open Lwt.Infix;

open Yojson;
open Yojson.Basic;
open Yojson.Basic.Util;

open Fetch;
open Fetch.Response;

let baseUrl = "http://workbook.HOSTNAME.com/api";
let toText = r => r.text();

let employeeUrl = baseUrl ++ "/resource/employees?Active=true";
let fetchEmployees = fetch(employeeUrl) >>= toText;

let rowUrl = (id, date) =>
  baseUrl
  ++ "/json/reply/TimeEntrySheetVisualizationRequest?ResourceId="
  ++ id
  ++ "&Date="
  ++ date;
let fetchRows = (id, date) => rowUrl(id, date) |> fetch >>= toText;

let entryUrl = (id, date) =>
  baseUrl
  ++ "/json/reply/TimeEntryDailyRequest?Week=true&ResourceId="
  ++ id
  ++ "&Date="
  ++ date;
let fetchEntries = (id, date) => entryUrl(id, date) |> fetch >>= toText;

let entryToJson =
    ({id, hours, taskId, billable, activityId, description}: Types.entry) =>
  Printf.sprintf(
    {|{
    "id": "%s",
    "hours": "%s",
    "taskId": "%s",
    "billable": "%s",
    "activityId": "%s",
    "description": "%s"
  }|},
    id,
    hours,
    taskId,
    billable,
    activityId,
    description,
  )
  |> Cohttp_lwt.Body.of_string;

let registerUrl = baseUrl ++ "/json/reply/TimeEntryUpdateRequest";
let postEntry = entry =>
  fetch(~method=Post, ~body=entryToJson(entry), registerUrl) >>= toText;