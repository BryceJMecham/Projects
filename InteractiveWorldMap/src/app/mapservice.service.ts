import { Injectable } from '@angular/core';
import { HttpClient   } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class MapserviceService {

  constructor(private http: HttpClient) { }

  public search(){
    return this.http.get('http://api.geonames.org/countryInfoJSON', {
      params: {
        username: 'brycejmecham'
      }
    });
  }

  public lowSearch(){
    return this.http.get('https://api.worldbank.org/V2/incomeLevel/LIC/country', {
      params: {
        format: 'json'
      }
    });
  }
  public middleSearch(){
    return this.http.get('https://api.worldbank.org/V2/incomeLevel/MIC/country', {
      params: {
        format: 'json'
      }
    });
  }
  public highSearch(){
    return this.http.get('https://api.worldbank.org/V2/incomeLevel/HIC/country', {
      params: {
        format: 'json'
      }
    });
  }
}
