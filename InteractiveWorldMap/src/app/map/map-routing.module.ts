import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { MapHomeComponent } from './map-home/map-home.component';

const routes: Routes = [
  {path: 'map', component: MapHomeComponent},
  {path: '', redirectTo:'/map', pathMatch:'full'}
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class MapRoutingModule { }
