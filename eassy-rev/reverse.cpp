void FUN_00102399(long param_1,int param_2)

{
  undefined *puVar1;
  ulong local_10;
  
  for (local_10 = 0; local_10 < (ulong)(long)param_2; local_10 = local_10 + 1) {
    puVar1 = (undefined *)FUN_00102d54(&DAT_0010b2a0,local_10 + param_1);
    *(undefined *)(local_10 + param_1) = *puVar1;
  }
  return;
}



void FUN_001023f3(long *param_1,int *param_2)

{
  int iVar1;
  long lVar2;
  void *pvVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  int iVar6;
  long in_FS_OFFSET;
  int local_1404;
  undefined local_13f8 [16];
  undefined local_13e8 [32];
  string local_13c8 [32];
  undefined local_13a8 [5000];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  FUN_00102c4e(local_13c8,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_{}",local_13e8);
  FUN_001030e6(local_13e8);
  FUN_00102d7a(local_13a8,0x2a);
  lVar2 = std::string::size();
  FUN_00102da0(local_13f8,0,lVar2 + -1);
  local_1404 = 0;
  FUN_00102b78(local_13e8);
  while (local_1404 < *param_2) {
    FUN_00102e96(local_13e8,*param_1 + (long)local_1404);
    iVar1 = local_1404 + 1;
    iVar6 = local_1404 % 3;
    local_1404 = iVar1;
    if (iVar6 == 0) {
      FUN_00102f50(local_13f8,local_13a8);
      uVar4 = std::string::operator[]((ulong)local_13c8);
      FUN_00102e96(local_13e8,uVar4);
    }
  }
  iVar1 = FUN_00102f7a(local_13e8);
  *param_2 = iVar1;
  pvVar3 = operator_new__((long)(*param_2 + 1));
  *param_1 = (long)pvVar3;
  lVar2 = *param_1;
  uVar4 = FUN_00102fe2(local_13e8);
  uVar5 = FUN_00102f9a(local_13e8);
  FUN_0010302e(uVar5,uVar4,lVar2);
  *(undefined *)((long)*param_2 + *param_1) = 0;
  FUN_00102e40(local_13e8);
  std::string::~string(local_13c8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    // WARNING: Subroutine does not return
    __stack_chk_fail();
  }
  return;
}



void FUN_001026b8(long param_1,int param_2)

{
  undefined8 local_10;
  
  for (local_10 = 0; local_10 < (ulong)(long)param_2; local_10 = local_10 + 1) {
    *(char *)(local_10 + param_1) = *(char *)(local_10 + param_1) % '@';
  }
  return;
}



undefined4 FUN_0010270b(int param_1,undefined8 *param_2)

{
  bool bVar1;
  void *pvVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ostream *poVar5;
  undefined4 unaff_R13D;
  long in_FS_OFFSET;
  int local_6c;
  void *local_68;
  ulong local_60;
  string local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  std::string::string(local_58);
  if (param_1 == 2) {
    std::string::operator=(local_58,(char *)param_2[1]);
    local_6c = std::string::length();
    pvVar2 = operator_new__((long)(local_6c + 1));
    local_68 = pvVar2;
    uVar3 = std::string::end();
    uVar4 = std::string::begin();
    FUN_00103079(uVar4,uVar3,pvVar2);
    *(undefined *)((long)local_6c + (long)local_68) = 0;
    FUN_00102399(local_68,local_6c);
    FUN_001023f3(&local_68,&local_6c);
    FUN_001026b8(local_68,local_6c);