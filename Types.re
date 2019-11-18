type entry = {
  id: string,
  jobId: string,
  hours: string,
  taskId: string,
  billable: bool,
  activityId: string,
  description: string,
  registrationDate: string,
};

type row = {
  jobId: string,
  taskId: string,
  jobName: string,
  activityId: string,
  children: list(entry),
  taskDescription: string,
};

type employee = {
  id: string,
  employeeName: string,
};